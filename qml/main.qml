import QtQuick
import QtCore
import QtQuick.Window
import FigmaQmlInterface
import Qt.labs.settings 1.0 // on 6.5 u dont need this, but 6.4 requires
import MQTTI

Window {
    visible: true
    title: qsTr("QmQttI")
    //set window size to UI size
    width: figma.implicitWidth
    height: figma.implicitHeight


    // FigmaQML

    FigmaQmlUi {
        id: figma
        anchors.centerIn: parent
    }

    function read_text(src_id: string, text: string) {
        console.log(src_id, text)
        switch(src_id) {
        case 'serverAddrss':
            Mqtti.server = text;
            settings.server = text
            break;
        case 'topic_subscribe':
            settings.topic_subscribe = text
            break;
        case 'message':
            settings.message = text
            break;
        case 'tag':
            settings.tag = text
            break;
        }
    }

    component MInput : Item {
        property alias text: input.text
        property string name
        property alias placeHolder: placeHolder.text
        clip: true
        Text {
            id: placeHolder
            anchors.centerIn: parent
            visible: !input.cursorVisible && input.text.length === 0
            font: input.font
            color: "gray"
            MouseArea{anchors.fill: parent; onClicked: (mouse) => input.forceActiveFocus();}
        }
        TextInput {
            id: input
            anchors.centerIn: parent
            font.pixelSize: 20
        }
        onTextChanged: read_text(name, text)
        onFocusChanged: read_text(name, text)
    }

    Settings {
        id: settings
        property string server: "test.mosquitto.org"
        property string topic_subscribe: "FigmaQML"
        property string topic_publish: "FigmaQML"
        property string message: ""
    }


    Component {
        id: serverAddress
        MInput {
            text: settings.server
            name: "serverAddress"
            Component.onCompleted: {
                Mqtti.server = text
            }
        }
    }

    Component {
        id: topic
        MInput {
            id: topic_item
            text: settings.topic_publish
            name: "topic_publish"
        }
    }

    Component {
        id: message
        MInput {
            placeHolder: "Write a message"
            text: settings.message
            name: "message"
        }
    }


    // handle mouse / touch clicks
    function clickEvent(element) {
        switch(element) {
        case 'subscribe_view':
            FigmaQmlSingleton.setView(1);
            break;
        case 'publish_view':
            FigmaQmlSingleton.setView(0);
            break;
        case 'subscribe':
            Mqtti.subscribe(settings.topic_subscribe)
            break;
        case 'publish':
            Mqtti.publishMessage(settings.topic_publish, settings.message);
            break;
        case 'remove':
            FigmaQmlSingleton.sendString('subscriptions', 'remove_topic');
            break;
        }
    }


    Connections {
        target: FigmaQmlSingleton
        // handle events
        function onEventReceived(element, event) {
            console.log(element, event)
            switch(event) {
            case 'click_event':
                clickEvent(element);
            }
        }

        function onViewLoaded(view) {
            console.log("view loaded", view);
            if(view === FigmaQmlSingleton.view(1)) {
                FigmaQmlSingleton.setSourceComponent("server_address", serverAddress)
                FigmaQmlSingleton.setSourceComponent("topic_subscribe", topic)
                FigmaQmlSingleton.setSource("subscriptions", "qrc:/qml/Subscriptions.qml") // absolute resource path needed
            }
            if(view === FigmaQmlSingleton.view(0)) {
                FigmaQmlSingleton.setSourceComponent("message", message)
                FigmaQmlSingleton.setSourceComponent("topic_publish", topic)
                FigmaQmlSingleton.setSource("messages", "qrc:/qml/Messages.qml")
            }
        }
    }

    Connections {
        target: Mqtti
        function onError(error_msg) {
            console.log("MQTTI:", error_msg)
        }
    }

    // initial read from settings and set
    Component.onCompleted: {
        Mqtti.server = settings.server;
    }
}
