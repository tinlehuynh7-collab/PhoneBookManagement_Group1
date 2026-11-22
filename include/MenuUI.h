#pragma once

#include <windows.h>
#include <commctrl.h>
#include <string>
#include <vector>
#include <unordered_map>
#include "AccountService.h"
#include "ContactService.h"
#include "GroupService.h"
#include "DBManager.h"
#include "Utils.h"

namespace UITheme
{
    // Modern Clean Color Palette (matching PBMS designs)
    constexpr COLORREF BgWindow      = RGB(248, 250, 252); // #F8FAFC
    constexpr COLORREF BgCard        = RGB(255, 255, 255); // #FFFFFF
    constexpr COLORREF BgTableHeader = RGB(241, 245, 249); // #F1F5F9
    constexpr COLORREF BgLightBlue   = RGB(239, 246, 255); // #EFF6FF
    constexpr COLORREF BgDanger      = RGB(254, 242, 242); // #FEF2F2
    constexpr COLORREF BgWarning     = RGB(254, 243, 199); // #FEF3C7
    constexpr COLORREF BgHover       = RGB(241, 245, 249); // #F1F5F9
    constexpr COLORREF BgSelected    = RGB(239, 246, 255); // #EFF6FF

    constexpr COLORREF BorderLight   = RGB(226, 232, 240); // #E2E8F0
    constexpr COLORREF BorderInput   = RGB(203, 213, 225); // #CBD5E1
    constexpr COLORREF BorderBlue    = RGB(191, 219, 254); // #BFDBFE
    constexpr COLORREF BorderDanger  = RGB(254, 202, 202); // #FECACA
    constexpr COLORREF BorderWarning = RGB(253, 230, 138); // #FDE68A

    constexpr COLORREF PrimaryBlue   = RGB(37, 99, 235);   // #2563EB
    constexpr COLORREF PrimaryHover  = RGB(29, 78, 216);   // #1D4ED8
    constexpr COLORREF DangerRed     = RGB(220, 38, 38);   // #DC2626
    constexpr COLORREF DangerHover   = RGB(185, 28, 28);   // #B91C1C
    constexpr COLORREF StarGold      = RGB(245, 158, 11);  // #F59E0B
    constexpr COLORREF WarningText   = RGB(146, 64, 14);   // #92400E
    constexpr COLORREF SuccessText   = RGB(21, 128, 61);   // #15803D
    constexpr COLORREF SuccessBg     = RGB(220, 252, 231); // #DCFCE7

    constexpr COLORREF TextPrimary   = RGB(15, 23, 42);    // #0F172A
    constexpr COLORREF TextBody      = RGB(51, 65, 85);    // #334155
    constexpr COLORREF TextMuted     = RGB(100, 116, 139); // #64748B
    constexpr COLORREF TextLight     = RGB(148, 163, 184); // #94A3B8
    constexpr COLORREF TextWhite     = RGB(255, 255, 255); // #FFFFFF
}

enum class ButtonStyle
{
    Primary,
    Outline,
    Danger,
    NavItem,
    NavItemActive,
    Link,
    IconPencil,
    IconTrash
};

struct ButtonConfig
{
    ButtonStyle style = ButtonStyle::Outline;
    std::wstring icon;
    bool isHot = false;
};

/**
 * @class MenuUI
 * @brief Modern Win32 GUI implementation for Phone Book Management System.
 * Rebuilt completely to match the PBMS modern UI mockups.
 */
class MenuUI
{
    friend LRESULT CALLBACK ModalDialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
    // Typography
    HFONT hFontTitleBig;      // 26pt bold (Main headers)
    HFONT hFontDialogTitle;  // 20pt bold (Dialog/Section headers)
    HFONT hFontSubtitle;     // 13pt regular (Subtitles)
    HFONT hFontLabel;        // 12pt semibold (Field labels)
    HFONT hFontBody;         // 13pt regular (Normal body/inputs)
    HFONT hFontBodyBold;     // 13pt semibold (Buttons, table headers)
    HFONT hFontSmall;        // 11pt regular (Meta/footnotes)
    HFONT hFontSmallBold;    // 11pt bold (Badges, tags)
    HFONT hFontMetricVal;    // 32pt bold (Big metrics)
    HFONT hFontIcons;        // 15pt symbol (Segoe UI Symbol)
    HFONT hFontIconsBig;     // 32pt symbol

    // GDI Brushes
    HBRUSH hBrushBg;
    HBRUSH hBrushCard;
    HBRUSH hBrushTableHeader;
    HBRUSH hBrushLightBlue;
    HBRUSH hBrushDanger;
    HBRUSH hBrushWarning;

    HWND hWnd;
    std::string currentScreen;
    std::string previousScreen;
    std::string currentRole;
    int selectedContactId;
    int selectedGroupId;
    int selectedAccountId;
    bool passwordVisible;

    // Filter states
    std::string searchQuery;
    int filterGroupId;
    bool filterOnlyFavorites;
    std::string adminUserSearchQuery;
    std::string adminUserRoleFilter;
    std::string adminUserStatusFilter;

    // Backup & Recovery state
    std::string backupFilePath;
    std::string restoreFilePath;
    bool restoreValidated;
    int restoreContactsCount;
    int restoreGroupsCount;
    int restoreUsersCount;
    bool restoreConfirmed;

    std::vector<HWND> screenControls;
    std::unordered_map<HWND, ButtonConfig> buttonConfigs;
    AccountService accountService;

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK ButtonSubclassProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

    void createFonts();
    void createBrushes();
    void destroyResources();
    void clearScreen();
    void resizeForScreen(const std::string& screen);

    // Screen views
    void showScreen(const std::string& screen);
    void showLogin();
    void showRegister();
    void showForgotPassword();
    void showContacts();
    void showAdminWorkspace(const std::string& subview);

    // Modal Dialogs
    void showAddContactDialog();
    void showEditContactDialog();
    void showContactDetailsModal();
    void showManageGroupsDialog();
    void showDeleteContactConfirm();
    void showAdminAddUserDialog();
    void showAdminConfirmRestore();

    // Widget factory helpers
    HWND createStyledButton(const wchar_t* text, int x, int y, int w, int h, int id, ButtonStyle style = ButtonStyle::Outline, const wchar_t* icon = nullptr);
    HWND createStyledEdit(const wchar_t* placeholder, int x, int y, int w, int h, int id, bool password = false);
    HWND createStyledCombo(int x, int y, int w, int h, int id);
    HWND createOwnerDrawList(int x, int y, int w, int h, int id, int itemHeight = 52);

    // Drawing routines
    void onPaint(HDC hdc, const RECT& rc);
    void drawLogin(HDC hdc, const RECT& rc);
    void drawRegister(HDC hdc, const RECT& rc);
    void drawForgotPassword(HDC hdc, const RECT& rc);
    void drawContactsDashboard(HDC hdc, const RECT& rc);
    void drawAdminWorkspace(HDC hdc, const RECT& rc);
    void drawAdminSidebar(HDC hdc, const RECT& rc);
    void drawAdminUsersView(HDC hdc, const RECT& rc);
    void drawAdminReportsView(HDC hdc, const RECT& rc);
    void drawAdminBackupView(HDC hdc, const RECT& rc);
    void drawAdminRecoveryView(HDC hdc, const RECT& rc);

    // Custom owner drawing
    void onDrawItem(DRAWITEMSTRUCT* pDIS);
    void drawCustomButton(DRAWITEMSTRUCT* pDIS);
    void drawContactListItem(DRAWITEMSTRUCT* pDIS);
    void drawAdminUserListItem(DRAWITEMSTRUCT* pDIS);

    // Command dispatcher
    void handleCommand(WPARAM wParam, LPARAM lParam);
    void handleLogin();
    void handleLogout();
    void handleClose();

    // Data helpers
    std::vector<Contact> getFilteredContacts() const;
    std::vector<AccountData> getFilteredAccounts() const;

public:
    MenuUI();
    ~MenuUI();
    int run();
};
