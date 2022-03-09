import QtQuick 2.4

Item {
    width: 400
    height: 400

    Rectangle {
        id: bg
        color: "#e3e3e3"
        anchors.fill: parent

        Rectangle {
            id: table
            x: 57
            y: 517
            width: 668
            height: 255
            color: "#939393"
            border.width: 3

            Rectangle {
                id: tablerows
                x: 0
                width: 131
                color: "#b9b9b9"
                border.width: 3
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.topMargin: 0
                anchors.bottomMargin: 0

                Text {
                    id: astartext
                    x: 15
                    y: 61
                    width: 95
                    height: 45
                    text: qsTr("ASTAR")
                    elide: Text.ElideLeft
                    font.pixelSize: "30"
                    horizontalAlignment: Text.AlignLeft
                    wrapMode: Text.NoWrap
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.strikeout: "false"
                    font.underline: "false"
                    font.bold: "false"
                    renderType: Text.QtRendering
                    textFormat: Text.AutoText
                    fontSizeMode: Text.FixedSize
                }

                Text {
                    id: bfstext
                    x: 15
                    y: 112
                    width: 95
                    height: 45
                    text: qsTr("BFS")
                    elide: Text.ElideLeft
                    font.pixelSize: "30"
                    horizontalAlignment: Text.AlignLeft
                    wrapMode: Text.NoWrap
                    anchors.horizontalCenter: parent.horizontalCenter
                    fontSizeMode: Text.FixedSize
                    font.underline: "false"
                    renderType: Text.QtRendering
                    textFormat: Text.AutoText
                    font.bold: "false"
                    font.strikeout: "false"
                }

                Text {
                    id: dfstext
                    x: 15
                    y: 163
                    width: 95
                    height: 45
                    text: qsTr("DFS")
                    elide: Text.ElideLeft
                    font.pixelSize: "30"
                    horizontalAlignment: Text.AlignLeft
                    wrapMode: Text.NoWrap
                    anchors.horizontalCenter: parent.horizontalCenter
                    fontSizeMode: Text.FixedSize
                    font.underline: "false"
                    renderType: Text.QtRendering
                    textFormat: Text.AutoText
                    font.strikeout: "false"
                    font.bold: "false"
                }
            }
            Rectangle {
                id: tablecolumns
                y: 0
                height: 47
                color: "#b9b9b9"
                border.width: 3
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                Text {
                    id: timetext
                    x: 132
                    y: 2
                    width: 149
                    height: 45
                    text: qsTr("TIME")
                    elide: Text.ElideLeft
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: "30"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.NoWrap
                    fontSizeMode: Text.FixedSize
                    font.underline: "false"
                    renderType: Text.QtRendering
                    textFormat: Text.AutoText
                    font.bold: "false"
                    font.strikeout: "false"
                }

                Text {
                    id: checkedtext
                    x: 295
                    y: 2
                    width: 160
                    height: 45
                    text: qsTr("CHECKED")
                    elide: Text.ElideLeft
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: "30"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.NoWrap
                    fontSizeMode: Text.FixedSize
                    font.underline: "false"
                    renderType: Text.QtRendering
                    textFormat: Text.AutoText
                    font.strikeout: "false"
                    font.bold: "false"
                }

                Text {
                    id: pathtext
                    x: 480
                    y: 2
                    width: 160
                    height: 45
                    text: qsTr("PATH")
                    elide: Text.ElideLeft
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: "30"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.NoWrap
                    fontSizeMode: Text.FixedSize
                    font.underline: "false"
                    renderType: Text.QtRendering
                    textFormat: Text.AutoText
                    font.bold: "false"
                    font.strikeout: "false"
                }
            }
        }

        Rectangle {
            id: numberoftests
            x: 57
            y: 111
            width: 244
            height: 59
            color: "#939393"

            TextInput {
                id: numberoftestsint
                x: 0
                y: 1
                width: 244
                height: 57
                text: qsTr("Number of tests")
                font.pixelSize: "29"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Rectangle {
            id: startbutton
            x: 825
            y: 111
            width: 297
            height: 59
            color: "#939393"

            Text {
                id: starttext
                x: 0
                y: 0
                width: 297
                height: 59
                text: qsTr("Start")
                font.pixelSize: "29"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75;height:800;width:1200}D{i:3}D{i:7}D{i:1}
}
##^##*/

