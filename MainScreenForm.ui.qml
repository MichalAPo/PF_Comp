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

        Text {
            id: text1
            x: 1171
            y: 8
            width: 189
            height: 87
            text: qsTr("XD")
            font.pixelSize: 12
            fontSizeMode: Text.Fit
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75;height:800;width:1200}
}
##^##*/

