//Generated by FigmaQML 3.1.0

import Qt5Compat.GraphicalEffects
import QtQuick
import QtQuick.Shapes
import FigmaQmlInterface
Rectangle {
// component (Instance) level: 0 Publish 
    id: figma_3_109
    // # "Publish"
    objectName:"Publish"
    x:0
    y:0
    width:309
    height:599
    color: "transparent"
    clip: true 
    Rectangle {
    // component (Instance) level: 0 Publish 
        id: figma_3_57
        // # "Publish"
        objectName:"Publish"
        x:0
        y:0
        width:309
        height:599
        color: "transparent"
        clip: false 
        Text {
        // component (Instance) level: 0 QMQTTI 
            id: figma_2_41
            // # "QMQTTI"
            objectName:"QMQTTI"
            x:24
            y:14
            width:159
            height:38
            color:"#ff000000"
            wrapMode: TextEdit.WordWrap
            text:"QMQTTI"
            font.family: "DejaVu Sans"
            font.italic: false
            font.letterSpacing: 0
            font.pixelSize: 20
            font.weight: Font.Normal
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        Shape {
        // component (Instance) level: 0 Rectangle 5 
            id: figma_3_43
            // # "Rectangle 5"
            objectName:"Rectangle 5"
            x:0
            y:0
            width:309
            height:599
            ShapePath {
                strokeColor: "transparent"
                strokeWidth:1
                fillColor:"#ff4756e2"
                // component (shapeFill) level: 0 
                id: svgpath_figma_3_43
                fillRule: ShapePath.WindingFill
                PathSvg {
                    id: path_0_figma_3_43
                    path: "M0 0L309 0L309 599L0 599L0 0Z"
                } 
            }
        property alias path: path_0_figma_3_43.path
        }
        Item {
        // component (Instance) level: 0 qml?messages.asLoader 
            id: figma_3_44
            // # "qml?messages.asLoader"
            objectName:"qml?messages.asLoader"
            x: 24
            y: 57
            width:263
            height:313
                Loader {
                    id: l_figma_3_44
                    anchors.fill: parent
                    onLoaded: FigmaQmlSingleton.sourceLoaded('messages')
                    onItemChanged: {if(!item) FigmaQmlSingleton.sourceError('messages');}
                    Connections {
                        target: FigmaQmlSingleton
                        onSetSource: {
                            if(element == 'messages')
                                l_figma_3_44.source = source;
                        }
                        onSetSourceComponent: {
                            if(element == 'messages')
                                l_figma_3_44.sourceComponent = sourceComponent;
                        }
                    }
                }
        }
        Button4_figma {
        // component (Instance) level: 0 qml?add_file.onClick 
            id: figma_3_47
            // # "qml?add_file.onClick"
            objectName:"qml?add_file.onClick"
            visible: false
            MouseArea {
                anchors.fill: parent
                onClicked: { FigmaQmlSingleton.eventReceived( 'add_file', 'click_event' ); }
                onPositionChanged: { FigmaQmlSingleton.eventReceived( 'add_file', 'mouse_move_event' ); }
                onPressAndHold: { FigmaQmlSingleton.eventReceived( 'add_file', 'press_and_hold_event' ); }
                onDoubleClicked: { FigmaQmlSingleton.eventReceived( 'add_file', 'double_clicked_event' ); }
                onPressed: { FigmaQmlSingleton.eventReceived( 'add_file', 'pressed_event' );}
                onReleased: { FigmaQmlSingleton.eventReceived( 'add_file', 'released_event' ); }
            }
            x:24
            y:535
            Shape {
            // component (Instance) level: 1 Rectangle 8 
                id: figma_i3_47_1_15
                // # "Rectangle 8"
                objectName:"Rectangle 8"
                x:0
                y:0
                width:113
                height:45
                ShapePath {
                    id: svgpath_figma_i3_47_1_15
                    strokeColor: "transparent"
                    strokeWidth:1
                    fillColor:"#ffd9d9d9"
                    // component (shapeFill) level: 1 
                    fillRule: ShapePath.WindingFill
                    PathSvg {
                        id: path_0_figma_i3_47_1_15
                        path: "M0 0L113 0L113 45L0 45L0 0Z"
                    } 
                }
            property alias path: path_0_figma_i3_47_1_15.path
            }
            Text {
            // component (Instance) level: 1 Add file 
                id: figma_i3_47_1_17
                // # "Add file"
                objectName:"Add file"
                x:17
                y:10
                width:76.3796
                height:24
                color:"#ff000000"
                wrapMode: TextEdit.WordWrap
                text:"Add file"
                font.family: "DejaVu Sans"
                font.italic: false
                font.letterSpacing: 0
                font.pixelSize: 20
                font.weight: Font.Normal
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
        Button4_figma {
        // component (Instance) level: 0 qml?subscribe_view.onClick 
            id: figma_3_48
            // # "qml?subscribe_view.onClick"
            objectName:"qml?subscribe_view.onClick"
            MouseArea {
                anchors.fill: parent
                onClicked: { FigmaQmlSingleton.eventReceived( 'subscribe_view', 'click_event' ); }
                onPositionChanged: { FigmaQmlSingleton.eventReceived( 'subscribe_view', 'mouse_move_event' ); }
                onPressAndHold: { FigmaQmlSingleton.eventReceived( 'subscribe_view', 'press_and_hold_event' ); }
                onDoubleClicked: { FigmaQmlSingleton.eventReceived( 'subscribe_view', 'double_clicked_event' ); }
                onPressed: { FigmaQmlSingleton.eventReceived( 'subscribe_view', 'pressed_event' );}
                onReleased: { FigmaQmlSingleton.eventReceived( 'subscribe_view', 'released_event' ); }
            }
            x:183
            y:26
            width:104
            height:20
            Shape {
            // component (Instance) level: 1 qml?subscribe_view_button.fillColor 
                id: figma_i3_48_1_15
                // # "qml?subscribe_view_button.fillColor"
                objectName:"qml?subscribe_view_button.fillColor"
                Connections { //makeComponentPropertyChangeHandler 
                    target: FigmaQmlSingleton
                    onValueChanged: {
                        switch(element) {
                            case 'subscribe_view_button': svgpath_figma_i3_48_1_15.fillColor = value; break;
                        }
                    }
                }
                x:0
                y:0
                width:104
                height:20
                ShapePath {
                    id: svgpath_figma_i3_48_1_15
                    strokeColor: "transparent"
                    strokeWidth:1
                    fillColor:"#ffd9d9d9"
                    // component (shapeFill) level: 1 
                    fillRule: ShapePath.WindingFill
                    PathSvg {
                        id: path_0_figma_i3_48_1_15
                        path: "M0 0L104 0L104 20L0 20L0 0Z"
                    } 
                }
            property alias path: path_0_figma_i3_48_1_15.path
            }
            Text {
            // component (Instance) level: 1 Subscribe 
                id: figma_i3_48_1_17
                // # "Subscribe"
                objectName:"Subscribe"
                x:16
                y:2
                width:70.2963
                height:15
                color:"#ff000000"
                wrapMode: TextEdit.WordWrap
                text:"Subscribe"
                font.family: "DejaVu Sans"
                font.italic: false
                font.letterSpacing: 0
                font.pixelSize: 12
                font.weight: Font.Normal
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
        Button4_figma {
        // component (Instance) level: 0 qml?publish.onClick 
            id: figma_3_49
            // # "qml?publish.onClick"
            objectName:"qml?publish.onClick"
            MouseArea {
                anchors.fill: parent
                onClicked: { FigmaQmlSingleton.eventReceived( 'publish', 'click_event' ); }
                onPositionChanged: { FigmaQmlSingleton.eventReceived( 'publish', 'mouse_move_event' ); }
                onPressAndHold: { FigmaQmlSingleton.eventReceived( 'publish', 'press_and_hold_event' ); }
                onDoubleClicked: { FigmaQmlSingleton.eventReceived( 'publish', 'double_clicked_event' ); }
                onPressed: { FigmaQmlSingleton.eventReceived( 'publish', 'pressed_event' );}
                onReleased: { FigmaQmlSingleton.eventReceived( 'publish', 'released_event' ); }
            }
            x:174
            y:535
            Shape {
            // component (Instance) level: 1 Rectangle 8 
                id: figma_i3_49_1_15
                // # "Rectangle 8"
                objectName:"Rectangle 8"
                x:0
                y:0
                width:113
                height:45
                ShapePath {
                    id: svgpath_figma_i3_49_1_15
                    strokeColor: "transparent"
                    strokeWidth:1
                    fillColor:"#ffd9d9d9"
                    // component (shapeFill) level: 1 
                    fillRule: ShapePath.WindingFill
                    PathSvg {
                        id: path_0_figma_i3_49_1_15
                        path: "M0 0L113 0L113 45L0 45L0 0Z"
                    } 
                }
            property alias path: path_0_figma_i3_49_1_15.path
            }
            Text {
            // component (Instance) level: 1 Subscribe 
                id: figma_i3_49_1_17
                // # "Subscribe"
                objectName:"Subscribe"
                x:17
                y:14
                width:76.3796
                height:16
                color:"#ff000000"
                wrapMode: TextEdit.WordWrap
                text:"Publish"
                font.family: "DejaVu Sans"
                font.italic: false
                font.letterSpacing: 0
                font.pixelSize: 13
                font.weight: Font.Normal
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
        Button4_figma {
        // component (Instance) level: 0 qml?publish.onClick 
            id: figma_40_34
            // # "qml?publish.onClick"
            objectName:"qml?publish.onClick"
            MouseArea {
                anchors.fill: parent
                onClicked: { FigmaQmlSingleton.eventReceived( 'publish', 'click_event' ); }
                onPositionChanged: { FigmaQmlSingleton.eventReceived( 'publish', 'mouse_move_event' ); }
                onPressAndHold: { FigmaQmlSingleton.eventReceived( 'publish', 'press_and_hold_event' ); }
                onDoubleClicked: { FigmaQmlSingleton.eventReceived( 'publish', 'double_clicked_event' ); }
                onPressed: { FigmaQmlSingleton.eventReceived( 'publish', 'pressed_event' );}
                onReleased: { FigmaQmlSingleton.eventReceived( 'publish', 'released_event' ); }
            }
            x:174
            y:535
            Shape {
            // component (Instance) level: 1 qml?publish_button.fillColor 
                id: figma_i40_34_1_15
                // # "qml?publish_button.fillColor"
                objectName:"qml?publish_button.fillColor"
                Connections { //makeComponentPropertyChangeHandler 
                    target: FigmaQmlSingleton
                    onValueChanged: {
                        switch(element) {
                            case 'publish_button': svgpath_figma_i40_34_1_15.fillColor = value; break;
                        }
                    }
                }
                x:0
                y:0
                width:113
                height:45
                ShapePath {
                    id: svgpath_figma_i40_34_1_15
                    strokeColor: "transparent"
                    strokeWidth:1
                    fillColor:"#ffd9d9d9"
                    // component (shapeFill) level: 1 
                    fillRule: ShapePath.WindingFill
                    PathSvg {
                        id: path_0_figma_i40_34_1_15
                        path: "M0 0L113 0L113 45L0 45L0 0Z"
                    } 
                }
            property alias path: path_0_figma_i40_34_1_15.path
            }
            Text {
            // component (Instance) level: 1 Subscribe 
                id: figma_i40_34_1_17
                // # "Subscribe"
                objectName:"Subscribe"
                x:17
                y:14
                width:76.3796
                height:16
                color:"#ff000000"
                wrapMode: TextEdit.WordWrap
                text:"Publish"
                font.family: "DejaVu Sans"
                font.italic: false
                font.letterSpacing: 0
                font.pixelSize: 13
                font.weight: Font.Normal
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
        Text {
        // component (Instance) level: 0 QMQTTI 
            id: figma_3_50
            // # "QMQTTI"
            objectName:"QMQTTI"
            x:24
            y:14
            width:159
            height:38
            color:"#ff000000"
            wrapMode: TextEdit.WordWrap
            text:"QMQTTI"
            font.family: "DejaVu Sans"
            font.italic: false
            font.letterSpacing: 0
            font.pixelSize: 20
            font.weight: Font.Normal
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        Qml_server_address_onClick2_figma {
        // component (Instance) level: 0 qml?message.onClick 
            id: figma_3_100
            // # "qml?message.onClick"
            objectName:"qml?message.onClick"
            MouseArea {
                anchors.fill: parent
                onClicked: { FigmaQmlSingleton.eventReceived( 'message', 'click_event' ); }
                onPositionChanged: { FigmaQmlSingleton.eventReceived( 'message', 'mouse_move_event' ); }
                onPressAndHold: { FigmaQmlSingleton.eventReceived( 'message', 'press_and_hold_event' ); }
                onDoubleClicked: { FigmaQmlSingleton.eventReceived( 'message', 'double_clicked_event' ); }
                onPressed: { FigmaQmlSingleton.eventReceived( 'message', 'pressed_event' );}
                onReleased: { FigmaQmlSingleton.eventReceived( 'message', 'released_event' ); }
            }
            x:23
            y:463
            Shape {
            // component (Instance) level: 1 Rectangle 8 
                id: figma_i3_100_3_93
                // # "Rectangle 8"
                objectName:"Rectangle 8"
                x:0
                y:1
                width:263
                height:48
                ShapePath {
                    id: svgpath_figma_i3_100_3_93
                    strokeColor: "transparent"
                    strokeWidth:1
                    fillColor:"#ffd9d9d9"
                    // component (shapeFill) level: 1 
                    fillRule: ShapePath.WindingFill
                    PathSvg {
                        id: path_0_figma_i3_100_3_93
                        path: "M0 0L263 0L263 48L0 48L0 0Z"
                    } 
                }
            property alias path: path_0_figma_i3_100_3_93.path
            }
            Item {
            // component (Instance) level: 1 qml?message.asLoader 
                id: figma_i3_100_3_94
                // # "qml?message.asLoader"
                objectName:"qml?message.asLoader"
                Connections { //makeComponentPropertyChangeHandler 
                    target: FigmaQmlSingleton
                    onValueChanged: {
                        switch(element) {
                        }
                    }
                }
                x: 0
                y: 0
                width:263
                height:49
                    Loader {
                        id: l_figma_i3_100_3_94
                        anchors.fill: parent
                        onLoaded: FigmaQmlSingleton.sourceLoaded('message')
                        onItemChanged: {if(!item) FigmaQmlSingleton.sourceError('message');}
                        Connections {
                            target: FigmaQmlSingleton
                            onSetSource: {
                                if(element == 'message')
                                    l_figma_i3_100_3_94.source = source;
                            }
                            onSetSourceComponent: {
                                if(element == 'message')
                                    l_figma_i3_100_3_94.sourceComponent = sourceComponent;
                            }
                        }
                    }
            }
        }
        Qml_server_address_onClick2_figma {
        // component (Instance) level: 0 qml?topic_publish.onClick 
            id: figma_28_27
            // # "qml?topic_publish.onClick"
            objectName:"qml?topic_publish.onClick"
            MouseArea {
                anchors.fill: parent
                onClicked: { FigmaQmlSingleton.eventReceived( 'topic_publish', 'click_event' ); }
                onPositionChanged: { FigmaQmlSingleton.eventReceived( 'topic_publish', 'mouse_move_event' ); }
                onPressAndHold: { FigmaQmlSingleton.eventReceived( 'topic_publish', 'press_and_hold_event' ); }
                onDoubleClicked: { FigmaQmlSingleton.eventReceived( 'topic_publish', 'double_clicked_event' ); }
                onPressed: { FigmaQmlSingleton.eventReceived( 'topic_publish', 'pressed_event' );}
                onReleased: { FigmaQmlSingleton.eventReceived( 'topic_publish', 'released_event' ); }
            }
            x:24
            y:390
            Shape {
            // component (Instance) level: 1 Rectangle 8 
                id: figma_i28_27_3_93
                // # "Rectangle 8"
                objectName:"Rectangle 8"
                x:0
                y:1
                width:263
                height:48
                ShapePath {
                    id: svgpath_figma_i28_27_3_93
                    strokeColor: "transparent"
                    strokeWidth:1
                    fillColor:"#ffd9d9d9"
                    // component (shapeFill) level: 1 
                    fillRule: ShapePath.WindingFill
                    PathSvg {
                        id: path_0_figma_i28_27_3_93
                        path: "M0 0L263 0L263 48L0 48L0 0Z"
                    } 
                }
            property alias path: path_0_figma_i28_27_3_93.path
            }
            Item {
            // component (Instance) level: 1 qml?topic_publish.asLoader 
                id: figma_i28_27_3_94
                // # "qml?topic_publish.asLoader"
                objectName:"qml?topic_publish.asLoader"
                Connections { //makeComponentPropertyChangeHandler 
                    target: FigmaQmlSingleton
                    onValueChanged: {
                        switch(element) {
                        }
                    }
                }
                x: 0
                y: 0
                width:263
                height:49
                    Loader {
                        id: l_figma_i28_27_3_94
                        anchors.fill: parent
                        onLoaded: FigmaQmlSingleton.sourceLoaded('topic_publish')
                        onItemChanged: {if(!item) FigmaQmlSingleton.sourceError('topic_publish');}
                        Connections {
                            target: FigmaQmlSingleton
                            onSetSource: {
                                if(element == 'topic_publish')
                                    l_figma_i28_27_3_94.source = source;
                            }
                            onSetSourceComponent: {
                                if(element == 'topic_publish')
                                    l_figma_i28_27_3_94.sourceComponent = sourceComponent;
                            }
                        }
                    }
            }
        }
    }
    Connections { //makePropertyChangeHandler 
         target: FigmaQmlSingleton
        onValueChanged: {
            switch(element) {
                case 'subscribe_view_button': figma_i3_48_1_15.fillColor = value; break;
                case 'publish_button': figma_i40_34_1_15.fillColor = value; break;
            }
        }
    }
}
