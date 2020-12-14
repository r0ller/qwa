import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    function startUpFunction(){
        //This is relevant for the Android code
        //that intercepts console log and this
        //indicates that qml has loaded and
        //opening webmessage channels can be started.
        console.log('qmlwasm1');
    }
    property alias aliasText1: text1.text
    Text {
        id: text1
        anchors.centerIn: parent
        text: qsTr("Hello World")
        color: "black"
    }

    Rectangle {
        id: rect1
        width: 50
        height: 50
        color: "red"
        Behavior on x { SpringAnimation { spring: 2; damping: 0.2 } }
        Behavior on y { SpringAnimation { spring: 2; damping: 0.2 } }
    }

    MouseArea {
        objectName: "mousearea"
        anchors.fill: parent
        onClicked: {
            rect1.x = mouse.x - rect1.width/2;
            rect1.y = mouse.y - rect1.height/2;
            msgBoard.postMessage("Hello from QML");
            //msgBoard.refresh();
        }
        function clickReturn(msg: string){
            console.log(msg);
            mainWindow.aliasText1=msg;
        }
    }
    Component.onCompleted: startUpFunction();
}
