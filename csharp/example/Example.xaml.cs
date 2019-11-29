//
// Demonstration on how to call custom 3ds Max notifications in C#.
// Works with 3ds Max 2019 and above.
// (c) 2019 Wesley Hill
//

using System;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Collections.Generic;
using UiViewModels.Actions;
using Autodesk.Max;

namespace Example
{
    public partial class Dialog : UserControl
    {
        public enum CustomNotificationChannels
        {
            Custom1 = 4098, // 0x00001002
            Custom2 = 4099, // 0x00001003
            Custom3 = 4100, // 0x00001004
            Custom4 = 4101, // 0x00001005
            Custom5 = 4102, // 0x00001006
            Custom6 = 4103, // 0x00001007
            Custom7 = 4104, // 0x00001008
        };
        public List<GlobalDelegates.Delegate5> handlers;
        public GlobalDelegates.Delegate5 notifHandler;

        public Dialog()
        {
            InitializeComponent();
            broadcastChannelsList.ItemsSource = Enum.GetValues(typeof(CustomNotificationChannels)).Cast<CustomNotificationChannels>().ToDictionary(x => (int)x, x => x.ToString());
            broadcastChannelsList.SelectedIndex = 0;
            broadcastChannelsList.DisplayMemberPath = "Value";
            handlers = new List<GlobalDelegates.Delegate5>();
        }

        private void RegisterNotification(object sender, RoutedEventArgs e)
        {
            if (handlers.Count == 1)
            {
                statusLabel.Content = "Notification already registered.";
            }
            else
            {
                notifHandler = new GlobalDelegates.Delegate5(Callback);
                KeyValuePair<int, string> result = (KeyValuePair<int, string>)broadcastChannelsList.SelectedValue;
                GlobalInterface.Instance.RegisterNotification(notifHandler, null, (SystemNotificationCode)result.Key);
                statusLabel.Content = "Notification registered.";
                handlers.Add(notifHandler);
            }
        }

        private void UnRegisterNotification(object sender, RoutedEventArgs e)
        {
            if (notifHandler != null)
            {
                GlobalInterface.Instance.UnRegisterNotification(notifHandler, null);
                statusLabel.Content = "Notification unregistered.";
                handlers.Remove(notifHandler);
                notifHandler = null;
            }
            else
            {
                statusLabel.Content = "Notification not registered.";
            }
        }

        private void ForceUnregisterNotification(object sender, RoutedEventArgs e)
        {
            if (handlers.Count == 1)
            {
                foreach (GlobalDelegates.Delegate5 handle in handlers)
                {
                    GlobalInterface.Instance.UnRegisterNotification(handle, null);
                }
                statusLabel.Content = "Notifications forcibly unregistered.";
                handlers.Remove(notifHandler);
                notifHandler = null;
            }
            else
            {
                statusLabel.Content = "Notification not registered.";
            }
        }

        private void InformationMessage(object sender, RoutedEventArgs e)
        {
            KeyValuePair<int, string> result = (KeyValuePair<int, string>)broadcastChannelsList.SelectedValue;
            Global.BroadcastNotification((SystemNotificationCode)result.Key);
        }

        private void Callback(IntPtr obj, INotifyInfo info)
        {
            MessageBox.Show("Hello World!", "Result");
        }

        public static IInterface14 Interface
        {
            get
            {
                return Global.COREInterface17;
            }
        }

        public static IGlobal Global
        {
            get
            {
                return GlobalInterface.Instance;
            }
        }
    }

	public class Metadata : CuiDockableContentAdapter
	{
		public override string ActionText { get { return "Custom Notifications Demo"; } }
		public override string Category { get { return "Example"; } }

		public override string WindowTitle
		{
			get { return "Custom Notifications Demo"; }
		}

		public override string ObjectName
		{
			get { return "Custom Notifications Demo"; }
		}

		public override Type ContentType
		{
			get { return typeof(Dialog); }
		}

		public override object CreateDockableContent()
		{
			return new Dialog();
		}

		public override DockStates.Dock DockingModes
		{
			get { return DockStates.Dock.Floating; }
		}
	}
}
