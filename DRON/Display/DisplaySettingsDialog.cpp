/**
 *  Display/DisplaySettingsDialog.cpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#include <DXGI.h>
#include <WindowsX.h>
#include <Commctrl.h>
#include <sstream>
#include <fstream>
#include <vector>
#include "DisplaySettingsDialog.hpp"
#include "../Resource.h"
#include "../Utility/DXUtil.hpp"

#include <strsafe.h>

DisplaySettingsDialog::DisplaySettingsDialog(HINSTANCE instance )
    : BaseWindow(instance, true), _parentwindow( 0 ), _is_ingame( false )
{ }

DisplaySettingsDialog::DisplaySettingsDialog(HINSTANCE instance, HWND parent, DisplaySettings& ds )
    : BaseWindow(instance, true), _parentwindow(parent),
      _is_ingame( true ), _settings( ds )
{ 
}

DisplaySettingsDialog::~DisplaySettingsDialog()
{ }

bool DisplaySettingsDialog::Show()
{
    if( DialogBoxParam( _instance, MAKEINTRESOURCE( DLG_DISPLAYSETTINGSDIALOG ),
        _parentwindow, ( DLGPROC )BaseWindowProc, ( LPARAM )this )
            == IDOK )
        return true;

    return false;
}

const DisplaySettings& DisplaySettingsDialog::GetDisplaySettings() const
{
    return _settings;
}

LRESULT CALLBACK DisplaySettingsDialog::Proc( HWND window, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch ( msg )
	{
	    case WM_INITDIALOG:
		    OnInitDialog( window );
            return true;
     
	    case WM_COMMAND:

            switch( LOWORD( wParam ) )
            {
                case IDC_DSDLG_FULLSCREEN:
                    OnToggleFullscreen( window );
                    return true;

                case IDC_DSDLG_SAVESETTINGS:
                    OnToggleSaveSettings( window );
                    return true;

                case IDOK:
                    OnOK( window );
                    EndDialog( window, IDOK );
                    return true;

                case IDCANCEL:
                    EndDialog( window, IDCANCEL );
                    return true;
            }
    } 
	return false;
}

void DisplaySettingsDialog::OnInitDialog( HWND window )
{
    // if we're booting up, try to load saved settings
    if( !_is_ingame )
    {
        // luaL_dofile returns 0 on success
		/*
        if( !luaL_dofile( _ls, "Data/Scripts/Settings.lua") )
        {
            if( LoadSettings() )
                EndDialog( window, IDOK );
        }
		*/
    }

    // We failed to load any settings or are ingame,
    // so we populate the combobox
	HWND combo_box = GetDlgItem( window, IDC_DSDLG_COMBOBOX );

    // enumerate the display modes...
    std::vector< DXGI_MODE_DESC > dmd_vec;
    EnumerateDisplayModes( dmd_vec );

    // ///and populate the combobox.
    std::wstringstream wbuffer;
    unsigned int width = 0;
    unsigned int height = 0;
    for( std::vector< DXGI_MODE_DESC >::size_type i = 0; i < dmd_vec.size(); ++i )
    {
        /* there are multiple modes with the same width/height,
         * so if we've used this res already, we skip this iteration */
        wbuffer.str( L"" );
        if( width == dmd_vec[ i ].Width && height == dmd_vec[ i ].Height )
        {
            continue;
        }
        else
        {
            // build this mode's text string and add it to the combo box
            width = dmd_vec[ i ].Width;
            height = dmd_vec[ i ].Height;
            wbuffer << dmd_vec[ i ].Width << L" x " << dmd_vec[ i ].Height;
            ComboBox_AddString( combo_box, wbuffer.str().c_str() );
        }
    }

    //if we're ingame we set the default to current settings
    if( _is_ingame )
    {
        wbuffer.str( L"" );
        wbuffer << _settings._width << L" x " << _settings._height;
        int idx = ComboBox_FindString( combo_box, -1, wbuffer.str().c_str() );
        if( idx != CB_ERR)
            ComboBox_SetCurSel( combo_box, idx );
        else
            ComboBox_SetCurSel( combo_box, 0 );
    }
    else
        ComboBox_SetCurSel( combo_box, 0 );
}

void DisplaySettingsDialog::OnToggleFullscreen(HWND window)
{
    HWND fullscreen = GetDlgItem(window, IDC_DSDLG_FULLSCREEN);
    LRESULT state = Button_GetCheck( fullscreen );
    
    if(state == BST_CHECKED)
        Button_SetCheck( fullscreen, BST_UNCHECKED );
    else
        Button_SetCheck( fullscreen, BST_CHECKED );
}

void DisplaySettingsDialog::OnToggleSaveSettings(HWND window)
{
    HWND save_settings = GetDlgItem(window, IDC_DSDLG_SAVESETTINGS);
    LRESULT state = Button_GetCheck( save_settings );

    if(state == BST_CHECKED)
        Button_SetCheck( save_settings, BST_UNCHECKED );
    else
        Button_SetCheck( save_settings, BST_CHECKED );
}

void DisplaySettingsDialog::OnOK( HWND window )
{
    // Get the selected item from the combo box
    // and parse it for window resolution
    HWND combo_box = GetDlgItem( window, IDC_DSDLG_COMBOBOX );

    LRESULT idx = ComboBox_GetCurSel( combo_box );
    int strlen = ComboBox_GetLBTextLen( combo_box, idx );
    std::vector< TCHAR > vbuffer( strlen + 1 );
    ComboBox_GetLBText( combo_box, idx, &vbuffer[ 0 ] );

    std::wstringstream wbuffer;
    wbuffer << std::wstring( vbuffer.begin(), vbuffer.end() );

    TCHAR dummy;
    wbuffer >> _settings._width >> dummy >> _settings._height;

    // fullscreen?
    HWND fullscreen = GetDlgItem( window, IDC_DSDLG_FULLSCREEN );
    LRESULT is_checked = Button_GetCheck( fullscreen );

    if( is_checked == BST_CHECKED )
        _settings._fullscreen = true;
    else
        _settings._fullscreen = false;

    // Save the settings in a LUA file if directed.
    HWND save_settings = GetDlgItem( window, IDC_DSDLG_SAVESETTINGS );
    is_checked = Button_GetCheck( save_settings );

    if( is_checked == BST_CHECKED )
    {
        std::ofstream file( "Data//Scripts//Settings.lua" );
        file << "display = {}" << std::endl
             << "display['width'] = " << _settings._width << std::endl
             << "display['height'] = " << _settings._height << std::endl
             << "display['fullscreen'] = ";

        if( _settings._fullscreen )
            file << "true" << std::endl;
        else
            file << "false" << std::endl;
    }
}

bool DisplaySettingsDialog::LoadSettings()
{
	/*
    luabind::object d = luabind::globals( _ls )[ "display" ];
    DisplaySettings ds;
    if( luabind::type( d ) == LUA_TTABLE )
    {
        ds._width = luabind::object_cast< unsigned int >( d[ "width" ] );
        ds._height = luabind::object_cast< unsigned int >( d[ "height" ] );
        ds._fullscreen = luabind::object_cast< bool >( d[ "fullscreen" ] );

        return ValidateSettings( ds );
    }
	*/

    return false;
}

// The settings won't be saved to the class member unless they validate.
bool DisplaySettingsDialog::ValidateSettings( DisplaySettings& ds )
{
    // enumerate the display modes...
    std::vector< DXGI_MODE_DESC > dmd_vec;
    EnumerateDisplayModes( dmd_vec );

    // now we validate the settings by trying to find a matching display mode
    unsigned int width = 0;
    unsigned int height = 0;
    for( std::vector< DXGI_MODE_DESC >::size_type i = 0; i < dmd_vec.size(); ++i )
    {
        if( ds._width == dmd_vec[ i ].Width &&
            ds._height == dmd_vec[ i ].Height )
        {
            // Loaded settings validate, so save and return true.
            _settings = ds;
            return true;
        }
    }

    return false;
}

void DisplaySettingsDialog::EnumerateDisplayModes( std::vector< DXGI_MODE_DESC >& dmd_vec )
{
    // use this to enumerate displays
    IDXGIFactory* factory_ptr;
    CreateDXGIFactory( __uuidof( IDXGIFactory ), ( void** )&factory_ptr );
    
    // Just use the first adapter (video card). We really should go through
    //  them all, though.
    IDXGIAdapter* adapter_ptr;
    factory_ptr->EnumAdapters( 0, &adapter_ptr );
 
    // And just use the adapter's first output. As above, we should really
    // iterate through them all.
    IDXGIOutput* output_ptr;
    adapter_ptr->EnumOutputs( 0, &output_ptr );
 
    // determine how many display nodes match our requested format.
    unsigned int num_modes;
    output_ptr->GetDisplayModeList( DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &num_modes, 0 );
 
    // collect the matching display modes into an array
    dmd_vec.resize( num_modes );
    output_ptr->GetDisplayModeList( DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &num_modes, &dmd_vec[ 0 ] );//dmd_array );

    // just say no to memory leaks
    DXRelease( output_ptr );
    DXRelease( adapter_ptr );
    DXRelease( factory_ptr );
}