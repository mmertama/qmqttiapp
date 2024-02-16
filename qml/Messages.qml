import QtQuick
import FigmaQmlInterface
import MQTTI

Rectangle {
    id: main
    ListModel {
        id: model
    }
    ListView {
        id: view
        model: model
        anchors.fill: parent
        clip: true
        delegate: Row {
            Text {
                text: topic
                font.bold: true
            }
            Text {text: dir ? " < " : " > "}
            Text {
                text: message
            }
        }
    }

    Component.onCompleted: {
        for(let i = 0; i < Mqtti.recordsSize(); ++i) {
            const msg = Mqtti.recordMessage(i);
            const tpc = Mqtti.recordTopic(i);
            const dir = Mqtti.recordOutwards(i);
            model.append({topic: tpc, message: msg, dir: dir})
        }
    }


    Connections {
        target: Mqtti
        function onRecordsChanged() {
            const hsz = Mqtti.recordsSize();
            if(hsz === 0) {
                model.clear();
            } else {
                const msg = Mqtti.recordMessage(hsz - 1);
                const tpc = Mqtti.recordTopic(hsz - 1);
                const dir = Mqtti.recordOutwards(hsz - 1);
                console.log(tpc, msg, dir);
                model.append({topic: tpc, message: msg, dir: dir})
            }
        }
    }
}
