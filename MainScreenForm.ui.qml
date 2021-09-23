import QtQuick 2.4

Item {
    width: 400
    height: 400

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 1200
        height: 800
        color: "#ffffff"

        Rectangle {
            id: rectangle2
            x: 13
            y: 577
            width: 640
            height: 215
            color: "#939393"
            border.width: 3

            Rectangle {
                id: rectangle1
                x: 0
                y: 0
                width: 131
                height: 215
                color: "#b9b9b9"
                border.width: 3
            }

            Rectangle {
                id: rectangle4
                x: 0
                y: 0
                width: 640
                height: 47
                color: "#b9b9b9"
                border.width: 3
            }

            Text {
                id: text1
                x: 15
                y: 61
                width: 95
                height: 45
                text: qsTr("ASTAR")
                elide: Text.ElideLeft
                font.pixelSize: "30"
                horizontalAlignment: Text.AlignLeft
                wrapMode: Text.NoWrap
                font.strikeout: "false"
                font.underline: "false"
                font.bold: "false"
                renderType: Text.QtRendering
                textFormat: Text.AutoText
                fontSizeMode: Text.FixedSize
            }

            Text {
                id: text3
                x: 15
                y: 163
                width: 95
                height: 45
                text: qsTr("DFS")
                elide: Text.ElideLeft
                font.pixelSize: "30"
                horizontalAlignment: Text.AlignLeft
                wrapMode: Text.NoWrap
                fontSizeMode: Text.FixedSize
                font.underline: "false"
                renderType: Text.QtRendering
                textFormat: Text.AutoText
                font.strikeout: "false"
                font.bold: "false"
            }

            Text {
                id: text2
                x: 15
                y: 112
                width: 95
                height: 45
                text: qsTr("BFS")
                elide: Text.ElideLeft
                font.pixelSize: "30"
                horizontalAlignment: Text.AlignLeft
                wrapMode: Text.NoWrap
                fontSizeMode: Text.FixedSize
                font.underline: "false"
                renderType: Text.QtRendering
                textFormat: Text.AutoText
                font.bold: "false"
                font.strikeout: "false"
            }

            Text {
                id: text4
                x: 132
                y: 2
                width: 149
                height: 45
                text: qsTr("TIME")
                elide: Text.ElideLeft
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
                id: text5
                x: 295
                y: 2
                width: 160
                height: 45
                text: qsTr("CHECKED")
                elide: Text.ElideLeft
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
                id: text6
                x: 480
                y: 2
                width: 160
                height: 45
                text: qsTr("PATH")
                elide: Text.ElideLeft
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

        Rectangle {
            id: rectangle3
            x: 8
            y: 111
            width: 244
            height: 59
            color: "#939393"
            border.width: 3

            TextInput {
                id: textInput
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
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75;height:800;width:1200}D{i:4}D{i:6}D{i:7}D{i:8}D{i:9}D{i:10}
D{i:2}
}
##^##*/

