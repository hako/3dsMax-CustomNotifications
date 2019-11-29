/*
*   Demonstration on how to call custom 3ds Max notifications in MaxScript.
*	Works with 3ds Max 2019 and above.
*	(c) 2019 Wesley Hill
*/

(

MaxPlus = python.Import "MaxPlus"

custom_notification_channels = #(
	#("Custom1", (dotNetClass "Autodesk.Max.SystemNotificationCode").Custom1, 4098), -- 0x00001002
	#("Custom2", (dotNetClass "Autodesk.Max.SystemNotificationCode").Custom2, 4099), -- 0x00001003
	#("Custom3", (dotNetClass "Autodesk.Max.SystemNotificationCode").Custom3, 4100), -- 0x00001004
	#("Custom4", (dotNetClass "Autodesk.Max.SystemNotificationCode").Custom4, 4101), -- 0x00001005
	#("Custom5", (dotNetClass "Autodesk.Max.SystemNotificationCode").Custom5, 4102), -- 0x00001006
	#("Custom6", (dotNetClass "Autodesk.Max.SystemNotificationCode").Custom6, 4103), -- 0x00001007
	#("Custom7", (dotNetClass "Autodesk.Max.SystemNotificationCode").Custom7, 4104)  -- 0x00001008
)

channelNames = for i = 1 to custom_notification_channels.count collect custom_notification_channels[i][1]
selected_data = #(custom_notification_channels[1][1], custom_notification_channels[1][2], custom_notification_channels[1][3]) -- default
notifHandler = undefined

(
	rollout ExampleAction "Click Broadcast Notification to send a callback.\n"  (
		dropdownlist dn "" items:channelNames
		button btn_rn_pressed "Register Notification" width:320 height:25
		button btn_un_pressed "Unregister Notification" width:320 height:25
		button btn_fun_pressed "Forcibly Unregister Notifications" width:320 height:25
		button btn_bn_pressed "Broadcast Notification" width:320 height:25
		label status_label "Ready." align:#left
				
		on btn_bn_pressed pressed do
		(
			(dotNetClass "Autodesk.Max.GlobalInterface").Instance.BroadcastNotification selected_data[2]
		)
		
		on btn_rn_pressed pressed do
		(
			if (MaxPlus.NotificationManager.Handlers.count == 1) then (
				status_label.text = "Notification already registered."
			) else (
				notifHandler = MaxPlus.NotificationManager.Register selected_data[3] callback
				status_label.text = "Notification registered."
			)
        )
				
		on btn_un_pressed pressed do
		(
			if (notifHandler != undefined) then (
				MaxPlus.NotificationManager.Unregister notifHandler
				notifHandler = undefined
				status_label.text = "Notification unregistered."
			) else (
				status_label.text = "Notification already unregistered."
			)
        )
		
		on btn_fun_pressed pressed do
		(
			if (MaxPlus.NotificationManager.Handlers.count == 1) then (
				for i = 1 to MaxPlus.NotificationManager.Handlers.count do (
					MaxPlus.NotificationManager.Unregister MaxPlus.NotificationManager.Handlers[i]
				)
				notifHandler = undefined
				status_label.text = "Notifications forcibly unregistered."
			) else (
				status_label.text = "Notifications not unregistered."
			)
        )

		on dn selected i do
		(
			selected_data = #(i, custom_notification_channels[i][2])
		)
		
		function callback code = (
			messageBox "Hello World!" title:"Result" 
		)
		
	)
		MainRollout = newRolloutFloater "Custom Notifications Demo" 315 200
		addRollout ExampleAction MainRollout
	)
)
