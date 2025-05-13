#pragma once
#ifndef _LANGUAGE_H
#define _LANGUAGE_H

#include "windows.h"

namespace langfile
{
	#define LANGUAGE				class
	#define REMOTE_ACCESSABLE_LIST	public
	#define STRING					LPCTSTR
	#define SHORT_STRING			PCWSTR
	#define AS						=
};

using namespace langfile;

LANGUAGE English
{
	REMOTE_ACCESSABLE_LIST:
	// Title Language
	STRING szMainSettings AS L"Main Settings";
	STRING szLMButton AS L"Left Mouse Button";
	STRING szRMButton AS L"Right Mouse Button";
	STRING szENBRightMouse AS L"Right mouse button: Just show menu";
	STRING szApply AS L"Apply";
	STRING szExit AS L"Exit";
	STRING szExpand AS L"Expand >>";
	STRING szCollapse AS L"<< Collapse";
	STRING szHelp AS L"Help";
	STRING szAbout AS L"About";
	STRING szDefault AS L"Default";
	STRING szAdvOpts AS L"Advanced Options";
	STRING szShowAtStartup AS L"Show this dialog box at startup";
	STRING szStartup AS L"Startup with Windows";
	STRING szAskBefore AS L"Ask before performing";
	STRING szSaveLog AS L"Save the log of actions";
	STRING szShowError AS L"Show error message on screen";
	STRING szRemindAction AS L"Remind before doing scheduled action";
	STRING szLanguage AS L"Language";
	STRING szViewLog AS L"View the log of actions";
	STRING szBackup AS L"Backup settings";
	STRING szSchedule AS L"Action Schedule";
	STRING szMainWnd AS L"Main Window";
	STRING szActionTitle AS L"Actions";

	// Combo Box Language
	STRING szScreenOff AS L"Screen off";
	STRING szSleep AS L"Sleep";
	STRING szShutdown AS L"Shut down";
	STRING szRestart AS L"Restart";
	STRING szLogOff AS L"Sign out";
	STRING szHibernate AS L"Hibernate";
	STRING szJustMenu AS L"Just show the menu";
	STRING szEnglish AS L"English";
	STRING szVietnamese AS L"Vietnamese";

	// Notify icon tips
	STRING szNotifyTip AS L"Click left mouse here to %s.\nClick right mouse to %s.";
	STRING szTipScreenOff AS L"turn off screen";
	STRING szTipSleep AS L"sleep";
	STRING szTipShutdown AS L"shut down";
	STRING szTipRestart AS L"restart";
	STRING szTipLogOff AS L"sign out";
	STRING szTipHibernate AS L"hibernate";
	STRING szTipMenu AS L"show menu";

	STRING szBalloonTipTitle AS L"Scheduled action is imminent";
	STRING szBalloonTipText AS L"%s in %d second(s).";
	STRING szBTipScreenOff AS L"The screen will turn off";
	STRING szBTipSleep AS L"The computer will sleep";
	STRING szBTipShutdown AS L"The computer will shut down";
	STRING szBTipRestart AS L"The computer will restart";
	STRING szBTipLogoff AS L"The current account will sign out";
	STRING szBTipHibernate AS L"The computer will hibernate";

	// Schedule dialog language
	STRING szCaption AS L"Schedule";
	STRING szActive AS L"Active schedule action";
	STRING szActionLabel AS L"Action";
	STRING szTimeSetting AS L"Time Setting";
	STRING szTimeLabel AS L"Time";
	STRING szDateLabel AS L"Date";
	STRING szEveryday AS L"Do schedule everyday";
	STRING szScdOK AS L"Save";
	STRING szScdCancel AS L"Close";
	STRING szScdMsgCpt AS L"Save options";
	STRING szScdMsg AS L"Some options has been changed.\nDo you want to save them?";

	// About dialog language
	STRING szCopyright AS L"Copyright (C) 2017 Stark Lee. All rights reserved.";
	STRING szAboutDev AS L"Developed by: Stark Lee (@starklee.developer)";
	STRING szFacebookLink AS L"<a>View Developer's Facebook Profile</a>";
	STRING szAppInfo1 AS L"PowerPlus - Quick power action utility\nDoing power action and setting up power schedule simplier.\n\n";
	STRING szAppInfo2 AS L"Developer's Profile:\nName: Stark Lee\nEmail: starklee2017@gmail.com\nFacebook: https://www.facebook.com/starklee.developer \nTwitter: https://twitter.com/starklee_dev \n\n";
	STRING szAppInfo3 AS L"Power Plus v2.0 STL is an utility which allow you to do some power actions quickly and to set up scheduled to do those actions. This tool help you to turn off screen, turn PC to sleep, shutdown, reboot, hibernate, and log off from current account just by one-click. It also help you to set an alarm to do those actions automatically.";
	STRING szOKButton AS L"Close";
};

LANGUAGE Vietnamese
{
	REMOTE_ACCESSABLE_LIST:
		// Title Language
		STRING szMainSettings AS L"Thiết lập chính";
		STRING szLMButton AS L"Nút chuột trái";
		STRING szRMButton AS L"Nút chuột phải";
		STRING szENBRightMouse AS L"Chuột phải: Chỉ hiển thị menu";
		STRING szApply AS L"Đóng";
		STRING szExit AS L"Thoát";
		STRING szExpand AS L"Mở rộng >>";
		STRING szCollapse AS L"<< Thu nhỏ";
		STRING szHelp AS L"Trợ giúp";
		STRING szAbout AS L"Giới thiệu";
		STRING szDefault AS L"Mặc định";
		STRING szAdvOpts AS L"Thiết lập Nâng cao";
		STRING szShowAtStartup AS L"Hiển thị hộp thoại này khi khởi động";
		STRING	szStartup AS L"Khởi động cùng Windows";
		STRING szAskBefore AS L"Hỏi trước khi thực hiện";
		STRING szSaveLog AS L"Lưu nhật ký hành động";
		STRING szShowError AS L"Hiển thị thông báo lỗi trên màn hình";
		STRING szRemindAction AS L"Nhắc nhở trước khi thực hiện lịch";
		STRING szLanguage AS L"Ngôn ngữ";
		STRING szViewLog AS L"Xem nhật ký hoạt động";
		STRING szBackup AS L"Sao lưu thiết lập";
		STRING szSchedule AS L"Hẹn giờ";
		STRING szMainWnd AS L"Hiện cửa sổ chính";
		STRING szActionTitle AS L"Hành động";

		// Combo Box Language
		STRING szScreenOff AS L"Tắt màn hình";
		STRING szSleep AS L"Ngủ";
		STRING szShutdown AS L"Tắt máy";
		STRING szRestart AS L"Khởi động lại";
		STRING szLogOff AS L"Đăng xuất";
		STRING szHibernate AS L"Ngủ đông";
		STRING szJustMenu AS L"Chỉ hiển thị menu";
		STRING szEnglish AS L"Tiếng Anh";
		STRING szVietnamese AS L"Tiếng Việt";

		// Notify icon tips
		STRING szNotifyTip AS L"Bấm chuột trái vào đây để %s.\nBấm chuột phải để %s.";
		STRING szTipScreenOff AS L"tắt màn hình";
		STRING szTipSleep AS L"chuyển sang chế độ ngủ";
		STRING szTipShutdown AS L"tắt máy";
		STRING szTipRestart AS L"khởi động lại";
		STRING szTipLogOff AS L"đăng xuất";
		STRING szTipHibernate AS L"chuyển sang chế độ ngủ đông";
		STRING szTipMenu AS L"hiển thị menu";

		STRING szBalloonTipTitle AS L"Hành động sắp diễn ra";
		STRING szBalloonTipText AS L"%s trong %d giây nữa.";
		STRING szBTipScreenOff AS L"Màn hình sẽ tắt";
		STRING szBTipSleep AS L"Máy tính sẽ chuyển sang chế độ ngủ";
		STRING szBTipShutdown AS L"Máy tính sẽ tắt";
		STRING szBTipRestart AS L"Máy tính sẽ khởi động lại";
		STRING szBTipLogoff AS L"Tài khoản hiện tại sẽ đăng xuất";
		STRING szBTipHibernate AS L"Máy tính sẽ chuyển sang chế độ ngủ đông";

		// Schedule dialog language
		STRING szCaption AS L"Hẹn giờ";
		STRING szActive AS L"Kích hoạt chức năng lịch hoạt động";
		STRING szActionLabel AS L"Hành động";
		STRING szTimeSetting AS L"Thiết lập thời gian";
		STRING szTimeLabel AS L"Giờ";
		STRING szDateLabel AS L"Ngày";
		STRING szEveryday AS L"Thực hiện hành động hàng ngày";
		STRING szScdOK AS L"Lưu";
		STRING szScdCancel AS L"Đóng";
		STRING szScdMsgCpt AS L"Lưu thiết lập";
		STRING szScdMsg AS L"Một số thiết lập đã bị thay đổi.\nBạn có muốn lưu chúng lại không?";

		// About dialog language
		STRING szCopyright AS L"Bản quyền thuộc Stark Lee (2017). Mọi quyền được bảo lưu.";
		STRING szAboutDev AS L"Phát triển bởi: Stark Lee (@starklee.developer)";
		STRING szFacebookLink AS L"<a>Xem trang Facebook cá nhân của tác giả</a>";
		STRING szAppInfo1 AS L"PowerPlus - Tiện ích tắt máy tính nhanh\nTắt máy và hẹn giờ tắt nhanh hơn và đơn giản hơn.\n\n";
		STRING szAppInfo2 AS L"Thông tin người phát triển:\nTên: Stark Lee\nEmail: starklee2017@gmail.com\nFacebook: https://www.facebook.com/starklee.developer \nTwitter: https://twitter.com/starklee_dev \n\n";
		STRING szAppInfo3 AS L"PowerPlus v2.0 STL là một tiện ích cho phép người dùng thực hiện các hành động nguồn điện và hẹn giờ một cách nhanh chóng. Nó giúp bạn tắt màn hình, chuyển máy tính sang chế độ ngủ và ngủ đông, tắt máy, khởi động lại và đăng xuất chỉ bằng một cú nhấp chuột. Nó cũng giúp bạn hẹn giờ để thực hiện những hành động này một cách tự động.";
		STRING szOKButton AS L"Đóng";
};
#endif // !_LANGUAGE_H
