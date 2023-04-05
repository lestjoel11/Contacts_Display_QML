import QtQuick
import QtQuick.Window
import ContactList
Window {
    id: main
    visible: true
    title: qsTr("Hello World")
    ListView {
        id: contactList
    }
    Row {
        id: titleRow
        anchors { leftMargin: 30 }
        Text {
            id: pageTitle
            text: qsTr("Contacts")
            font { pointSize: 30 }
        }
    }
    Column {
        anchors.top: titleRow.bottom
        Rectangle {
            id: avatar
            width: 50
            height: width
            color: "orange"
            border { color: "black"; width: 1 }
            radius: width*0.5
            Text {
                anchors.centerIn : parent
                color: "red"
                text: "L"
                font { pointSize: 26; bold: true}
            }
            Rectangle {
                id: contactCard
                anchors { left: avatar.right; leftMargin: 10}
                width: 250
                height: 50
                border { color: "black"; width: 2}
                radius: 5

                Text {
                    id: contactName
                    text: qsTr("Wilma Whitehead") // Contact Name
                    font { pointSize: 22; }
                    anchors { horizontalCenter: parent.horizontalCenter }
                }
            }
        }
    }
}
