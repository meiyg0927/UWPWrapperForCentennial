//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

// UWPWrappers.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
using namespace std;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Globalization;
using namespace Windows::System;
using namespace Windows::ApplicationModel;
using namespace Windows::System;
using namespace Windows::UI::Notifications;
using namespace Windows::Data::Xml::Dom;

ToastNotification^ toast = nullptr;
ToastNotifier^ notifier = nullptr;

DllExport bool __stdcall LaunchMap(double lat, double lon)
{
	try
	{
		//
		// format the URI to match the defined protocol:
		// desktopbridgemapsample://location?lat={latitude}&?lon={longitude}
		//
		String ^str = ref new String(L"desktopbridgemapsample://");
		Uri ^uri = ref new Uri(str + L"location?lat=" + lat.ToString() + L"&?lon=" + lon.ToString());
		Launcher::LaunchUriAsync(uri);
	}
	catch (Exception^ ex) { return false; }
	return true;
}

DllExport bool __stdcall CreateToast(int index)
{
	String ^file = ref new String();
	String ^text = ref new String();

	//
	// set text and image of the toast based on the landmark
	//
	switch (index)
	{
	case 0:
		file = L"TowerBridge.png";
		text = "Tower Bridge of London";
		break;
	case 1:
		file = L"SyndeyOpera.png";
		text = "Sydney Opera";
		break;
	case 2:
		file = L"StatueOfLiberty.png";
		text = "Statue of Liberty";
		break;
	case 3:
		file = L"Space Needle.png";
		text = "Seattle Space Needle";
		break;
	case 4:
		file = L"Tokyo.png";
		text = "Tokyo Tower";
		break;
	}

	String ^xml = "<toast><visual><binding template='ToastGeneric'><image src='Assets/" + file + "'/><text hint-maxLines='1'>New Landmark</text><text>" + text + "</text></binding></visual></toast>";
	try
	{
		if (notifier == nullptr)
		{
			notifier = ToastNotificationManager::CreateToastNotifier();
		}
		else
		{
			notifier->Hide(toast);
		}
		XmlDocument^ toastXml = ref new XmlDocument();
		toastXml->LoadXml(xml);
	
		toast = ref new ToastNotification(toastXml);
		notifier->Show(toast);
	}
	catch (Exception^ ex) { return false; }
	return true;
}

DllExport bool __stdcall CreateTile(int index)
{
	try
	{
		//String ^xml = "<tile><visual><binding template='TileWide'><image placement='peek' src='Assets/Apps/icon2.jpg'/><group><subgroup><text hint-style='subtitle'>James Parker</text><text hint-style='captionSubtle'>Photos from your trip</text><text hint-style='captionSubtle'>Check out these awesome photos I took while in New York!</text></subgroup><subgroup><text hint-style='subtitle'>Jennifer Parker</text><text hint-style='captionSubtle'>Photos from our trip</text><text hint-style='captionSubtle'>Check out these awesome photos I took while in New Zealand!</text></subgroup></group></binding></visual></tile>";
		//String ^xml = "<tile><visual><binding template='TileWide'><image placement='peek' src='Assets/Apps/icon2.jpg'/><text hint-style='subtitle'>James Parker</text><text hint-style='captionSubtle'>Photos from your trip</text><text hint-style='captionSubtle'>Check out these awesome photos I took while in New York!</text><text hint-style='subtitle'>Jennifer Parker</text><text hint-style='captionSubtle'>Photos from our trip</text><text hint-style='captionSubtle'>Check out these awesome photos I took while in New Zealand!</text></binding></visual></tile>";
		//String ^xml = "<tile><visual><binding template='TileWide'><group><subgroup><image placement='peek' src='Assets/Apps/icon2.jpg'/></subgroup><subgroup><image placement='peek' src='Assets/Apps/icon1.png'/></subgroup></group></binding></visual></tile>";
		String ^xml = "<tile><visual><binding template='TileSmall'><image placement='peek' src='Assets/Apps/icon0.jpg'/><image placement='background' src='Assets/AppSmallTile.scale-100.png' hint-removeMargin='true'/></binding><binding template='TileMedium'><image placement='peek' src='Assets/Apps/icon1.jpg'/><image placement='background' src='Assets/AppMedTile.scale-100.png' hint-removeMargin='true'/></binding><binding template='TileWide'><image placement='peek' src='Assets/Apps/icon2.jpg'/><image placement='background' src='Assets/AppWideTile.scale-100.png' hint-removeMargin='true'/></binding><binding template='TileLarge'><image placement='peek' src='Assets/Apps/icon3.jpg'/><image placement='background' src='Assets/AppLargeTile.scale-100.png' hint-removeMargin='true'/></binding></visual></tile>";		
		XmlDocument^ tileXml = ref new XmlDocument();
		tileXml->LoadXml(xml);
		TileNotification^ tileNotification = ref new TileNotification(tileXml);
		TileUpdateManager::CreateTileUpdaterForApplication()->Update(tileNotification);

	}
	catch (Exception^ ex) { return false; }
	return true;
}