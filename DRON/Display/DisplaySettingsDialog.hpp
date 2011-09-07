/**
 *  Display/DisplaySettingsDialog.hpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#ifndef _DISPLAY_SETTINGS_DIALOG_HPP_
#define _DISPLAY_SETTINGS_DIALOG_HPP_

#include <vector>
#include "DisplaySettings.hpp"
#include "BaseWindow.hpp"

struct DXGI_MODE_DESC;
class DisplaySettingsDialog : public BaseWindow
{
    public:
        DisplaySettingsDialog( HINSTANCE, HWND, DisplaySettings& );
        DisplaySettingsDialog( HINSTANCE );
		virtual ~DisplaySettingsDialog();

        bool Show();
        const DisplaySettings& GetDisplaySettings() const;

        LRESULT CALLBACK Proc( HWND, UINT, WPARAM, LPARAM );
        
    protected:
        HWND            _parentwindow;
        DisplaySettings _settings;
        bool            _is_ingame;

        void OnInitDialog( HWND );
        void OnToggleFullscreen( HWND );
        void OnToggleSaveSettings( HWND );
        void OnOK( HWND );
        bool LoadSettings();
        bool ValidateSettings( DisplaySettings& );
        void EnumerateDisplayModes( std::vector< DXGI_MODE_DESC >& );

        //prevent copying
        DisplaySettingsDialog( const DisplaySettingsDialog& );
        DisplaySettingsDialog& operator=( const DisplaySettingsDialog& );
};

#endif  _DISPLAY_SETTINGS_DIALOG_HPP_
