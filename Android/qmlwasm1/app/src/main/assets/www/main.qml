import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    function startUpFunction(){
        console.log('qmlwasm1');
    }
    Text {
        id: text1
        anchors.centerIn: parent
        text: qsTr("Hello World")
        color: "black"
    }

    MouseArea {
        objectName: "mousearea"
        anchors.fill: parent
        onClicked: {
            msgBoard.postMessage("Hello from QML");
            //var result = msgBoard.postMessage("Hello from QML")
            //console.log("Result of postMessage():", result)
            //msgBoard.refresh();
        }
        function clickReturn(msg: string){
            console.log(msg);
            mainWindow.text1.text=msg;
        }
    }
    Component.onCompleted: startUpFunction();
}
