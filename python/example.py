"""
    Demonstration on how to call custom 3ds Max notifications in Python.
	Works with 3ds Max 2019 and above.
	(c) 2019 Wesley Hill
"""

import MaxPlus

from PySide2 import QtCore, QtWidgets
from pymxs import runtime as rt

NOTIFICATION_CODE = rt.dotNetClass('Autodesk.Max.SystemNotificationCode')

NOTIF_CHANNELS = {
    'Custom1': (4098, NOTIFICATION_CODE.Custom1),  # 0x00001002
    'Custom2': (4099, NOTIFICATION_CODE.Custom2),  # 0x00001003
    'Custom3': (4100, NOTIFICATION_CODE.Custom3),  # 0x00001004
    'Custom4': (4101, NOTIFICATION_CODE.Custom4),  # 0x00001005
    'Custom5': (4102, NOTIFICATION_CODE.Custom5),  # 0x00001006
    'Custom6': (4103, NOTIFICATION_CODE.Custom6),  # 0x00001007
    'Custom7': (4104, NOTIFICATION_CODE.Custom7),  # 0x00001008
}


class Example(QtWidgets.QDialog):
    """
    Custom Notification Dialog
    This is an example tool which uses custom broadcast notifications.
    """

    sel_data = ('Custom1', sorted(NOTIF_CHANNELS.values())[0])
    notif_handler = None

    def __init__(self, ui_class, parent=None):
        super(Example, self).__init__(parent)

        self.status_bar = QtWidgets.QStatusBar()
        self.status_bar.setSizeGripEnabled(False)
        self.status_bar.showMessage('Ready.')

        self.ui = ui_class()
        self.ui.setupUi(self)

        self.ui.channels.addItems(sorted(NOTIF_CHANNELS.keys()))
        self.ui.channels.currentTextChanged.connect(self.selection_changed)

        self.ui.broadcast_button.clicked.connect(self.broadcast_notification)
        self.ui.register_button.clicked.connect(self.register)
        self.ui.unregister_button.clicked.connect(self.unregister)
        self.ui.force_unregister_button.clicked.connect(self.force_unregister)
        self.ui.status_bar_layout.addWidget(self.status_bar)

    def broadcast_notification(self):
        """Broadcasts a custom notification to a channel, triggering a callback."""
        rt.dotNetClass(
            'Autodesk.Max.GlobalInterface').Instance.BroadcastNotification(
                self.sel_data[1][1])

    def register(self):
        """ Registers a selected notification handler."""
        if len(MaxPlus.NotificationManager.Handlers) == 1:
            self.status_bar.showMessage('Notification already registered.')
            return
        notif_handler = MaxPlus.NotificationManager.Register(
            self.sel_data[1][0], self.callback)
        self.notif_handler = notif_handler
        self.status_bar.showMessage('Notification registered.')

    def unregister(self):
        """Unregisters selected notification handler."""
        if self.notif_handler is not None:
            MaxPlus.NotificationManager.Unregister(self.notif_handler)
            self.status_bar.showMessage('Notification unregistered.')
            self.notif_handler = None
            return
        self.status_bar.showMessage('Notification not registered.')

    def force_unregister(self):
        """Force unregisters all notification handlers."""
        if len(MaxPlus.NotificationManager.Handlers) == 1:
            for handle in MaxPlus.NotificationManager.Handlers:
                MaxPlus.NotificationManager.Unregister(handle)
            self.notif_handler = None
            self.status_bar.showMessage('Notifications forcibly unregistered.')
            return
        self.status_bar.showMessage('Notifications not registered.')

    def selection_changed(self, i):
        """Change selection of notification channel."""
        self.sel_data = (i, NOTIF_CHANNELS[i])

    def callback(self, *args):
        """An example callback."""
        QtWidgets.QMessageBox.information(self, 'Result', 'Hello World!')


def main():
    ui, _ = MaxPlus.LoadUiType('./ui/example.ui')
    instance = Example(ui, MaxPlus.GetQMaxMainWindow())
    instance.show()


if __name__ == '__main__':
    main()
