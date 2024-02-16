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
        focus: true
        keyNavigationEnabled: true
        highlightFollowsCurrentItem : true
        highlight: Rectangle {color: "lightsteelblue"}
        Keys.onPressed: {
              console.log("list: " + event.key + " : " + event.text)
        }
        delegate: Row {
            Text {
                text: topic
            }
        }

        MouseArea {
            anchors.fill: parent
            propagateComposedEvents: true
            onClicked: (mouse) => {
                mouse.accepted = false;
                view.forceActiveFocus();
                const ii = view.indexAt(mouse.x, mouse.y);
                if(ii >= 0) {
                    view.currentIndex = ii;
                }
            }
        }
    }


    Component.onCompleted: {
        Mqtti.subscriptions.forEach((el) => model.append({topic: el}))
    }

    Connections {
        target: Mqtti
        function onSubscriptionsChanged() {
            model.clear()
            Mqtti.subscriptions.forEach((el) => model.append({topic: el}))
        }
    }

    Connections {
        target: FigmaQmlSingleton
        function onStringReceived(key: string, value: string) {
            console.log(key, value)
            switch(value) {
            case 'remove_topic':
                Mqtti.unsubscribe(model.get(view.currentItem).topic)
            }
        }
    }
}
