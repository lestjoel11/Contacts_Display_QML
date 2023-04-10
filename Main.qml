import QtQuick
import QtQuick.Window
import ContactItems
Window {
    id: main
    visible: true
    title: qsTr("Hello World")

    property real captionFontSize : 12

    Row {
        id: titleRow
        anchors { leftMargin: 30 }
        Text {
            id: pageTitle
            text: qsTr("Contacts")
            font { pointSize: 30 }
        }
    }

    ListView {
        id: contactList
        spacing: 10
        anchors { fill: parent; topMargin: 50 }
        model: ContactItems {}
        delegate: listItem
    }

    Component {
        id: listItem
        Rectangle {
            color: "gray"
            height: 75
            width: main.width
                Rectangle {
                    id: avatar
                    width: 50
                    height: width
                    color: "orange"
                    border { color: "black"; width: 1 }
                    radius: width*0.5
                    anchors { verticalCenter: parent.verticalCenter }
                Text {
                    anchors.centerIn : parent
                    color: "red"
                    text: model.ContactName[0]
                    font { pointSize: 26; bold: true}
                }
                Rectangle {
                    id: contactCard
                    color: "transparent"
                    anchors { left: avatar.right; leftMargin: 15 }
                    width: 250 //Will need to make dynamic
                    height: 75 //Will need to make dynamic
                    Column {
                        id: detailsColumn
                        spacing: 2
                        Text {
                            id: contactName
                            text: model.ContactName // Contact Name
                            font { pointSize: 22; }
                        }
                        Text {
                            id: contactPhone
                            text: model.ContactPhone // Contact Number
                            font { pointSize: captionFontSize; }
                        }
                    }
                    Component.onCompleted: { console.log(model.ContactName[0]) }
                }

            }
        }
    }
}
