#ifndef REVERIE_ENTITIES_MENU_PAUSE_HPP_
#   define REVERIE_ENTITIES_MENU_PAUSE_HPP_

#include <vector>

#include "src/omicron/entity/Entity.hpp"

#include "src/entities/menu/setting_widget/EnumWidget.hpp"
#include "src/entities/menu/setting_widget/SliderWidget.hpp"

/*****************************************\
| Handles the in-game pause overlay menu. |
\*****************************************/
class PauseMenu : public omi::Entity {
public:

    //--------------------------------------------------------------------------
    //                                ENUMERATORS
    //--------------------------------------------------------------------------

    // the different menu
    enum MenuType
    {
        TYPE_MAIN = 0,
        TYPE_EXIT,
        TYPE_SETTINGS,
        TYPE_INPUT_SETTINGS,
        TYPE_AUDIO_SETTINGS,
        TYPE_GRAPHICS_SETTINGS
    };

    // the items on the main menu
    enum MainMenuItem
    {
        MAIN_RESUME = 0,
        MAIN_SETTINGS,
        MAIN_EXIT
    };

    // the items on the exit check menu
    enum ExitMenuItem
    {
        EXIT_NO = 0,
        EXIT_YES
    };

    // the items on the settings menu
    enum SettingsMenuItem
    {
        SETTINGS_INPUT = 0,
        SETTINGS_AUDIO,
        SETTINGS_GRAPHICS,
        SETTINGS_BACK
    };

    // the items on the input settings menu
    enum InputMenuItem
    {
        INPUT_LOOK = 0,
        INPUT_MOVE,
        INPUT_RESET_DEFAULTS,
        INPUT_APPLY,
        INPUT_BACK
    };

    // the items on the audio settings menu
    enum AudioMenuItem
    {
        AUDIO_MASTER = 0,
        AUDIO_FX,
        AUDIO_MUSIC,
        AUDIO_RESET_DEFAULTS,
        AUDIO_APPLY,
        AUDIO_BACK
    };

    // the items on the graphics settings menu
    enum GraphicsMenuItem
    {
        GRAPHICS_RESOLUTION = 0,
        GRAPHICS_FULLSCREEN,
        GRAPHICS_VSYNC,
        GRAPHICS_GAMMA,
        GRAPHICS_SHADOWS,
        GRAPHICS_RESET_DEFAULTS,
        GRAPHICS_APPLY,
        GRAPHICS_BACK
    };

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    PauseMenu();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    void init();

    /** Override */
    void update();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the current menu
    MenuType m_currentMenu;

    // is true if the escape key is currently down
    bool m_escDown;
    // is true if one of the arrow keys is down
    bool m_arrowDown;
    // is true if the accept key is down
    bool m_acceptDown;

    // the sprite for the menu overlay
    omi::Sprite* m_overlay;
    // the list of renderable text for the main menu
    std::vector<omi::Text*> m_mainText;
    // the text check if the user is sure they want to exit
    omi::Text* m_exitCheckText;
    // the list of renderable text for the exit menu
    std::vector<omi::Text*> m_exitText;
    // the list of renderable text on the settings menu
    std::vector<omi::Text*> m_settingsText;
    // the list of renderable text on the input settings menu
    std::vector<omi::Text*> m_inputText;
    // the list of widget for the input settings menu
    std::vector<SettingWidget*> m_inputWidgets;
    // the list of renderable text on the audio settings menu
    std::vector<omi::Text*> m_audioText;
    // the list of widgets for the audio settings menu
    std::vector<SettingWidget*> m_audioWidgets;
    // the list of renderable text on the graphics settings menu
    std::vector<omi::Text*> m_graphicsText;
    // the list of widgets for the graphics settings menu
    std::vector<SettingWidget*> m_graphicsWidgets;

    // the index of the currently selected menu item
    int m_currentIndex;
    // the list of items currently on the menu
    std::vector<omi::Text*> m_currentItems;
    // the list of widgets currently on the menu
    std::vector<SettingWidget*> m_currentWidgets;

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Updates logic for when the menu is open */
    void updateMenuLogic();

    /** Returns the previous menu */
    void back();

    /** Sets the colour of the current menu items */
    void setItemColours();

    /** Sets the colour of the current widgets */
    void setWidgetColours();

    /** Updates the menu to reflect a state change */
    void updateMenuState();

    //-----------------------------ACCEPT FUNCTIONS-----------------------------

    /** Performs the actions associated with the current context */
    void accept();

    /** Performs the accept action on the main menu */
    void acceptMainMenu();

    /** Performs the accept action on the exit menu */
    void acceptExitMenu();

    /** Performs the accept action on the settings menu */
    void acceptSettingsMenu();

    /** Performs the accept action on the input menu */
    void acceptInputMenu();

    /** Performs the accept action on the audio menu */
    void acceptAudioMenu();

    /** Performs the accept action on the graphics settings menu */
    void acceptGraphicsMenu();

    //--------------------------------VISIBILITY--------------------------------

    /** Sets the visibility of the given text list */
    void setTextListVisibility(
            std::vector<omi::Text*>& textList, bool visible );

    /** Sets the visibility of the given widget list */
    void setWidgetVisibility(
            std::vector<SettingWidget*> widgetList, bool visible );

    /** Hides all aspects of the menu */
    void hideAll();

    //------------------------------INITIALISATION------------------------------

    /** Initialises the components of the pause menu */
    void initComponents();

    /** Initialises the main menu components */
    void initMainMenuComponents();

    /** Initialises the exit menu components */
    void initExitMenuComponents();

    /** Initialises the settings menu components */
    void initSettingsMenuComponents();

    /** Initialises the input settings menu components */
    void initInputMenuComponents();

    /** Initialises the audio settings menu components */
    void initAudioMenuComponents();

    /** Initialises the graphics settings menu components */
    void initGraphicsMenuComponents();
};

#endif
