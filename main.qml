import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    Text {
        id: textoId
        text: qsTr("teste")
        x: parent.width/2
        y: parent.height/2

        font.pointSize: 30
    }
    Connections{
       /* target: teste

        function onTeste(a){
            textoId.text = a;
            textoId.color = "red";
        }*/
    }
}
