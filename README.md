# qmqttiapp
Messaging application on top of MQTT
Example for FigmaQML


## Figma
The UI is completely composed from [Figma desing](https://www.figma.com/file/e7IRRrQKk54Ui8Ss5DLDIU/QMQTTI?type=design&node-id=3%3A110&mode=design&t=3QmuhweRiG3hZGQw-1)
using FigmaQML

The initial UI is very ugly in purpose, but I hope it get improved over time by having improved UI design.

## Using

### Publish View

* Subscribe button.
    * Change to Subscribe view.
* Messages list.
    * Here exchanged message appear, i.e. ones you publish and you subscribe.
* Message input
    * Write a message.
* Topic  input.
    * Publish under the topic.
* Publish button.
    * Do publish.
    
### Subscribe view

* Publish button.
    *  Change to publish view.
* Subscription view.
    * Here you can see subscribed topics.
* Topic input.
    * Enter topic to subscribe.
* Unsubscribe button.
    * Pick a topic from Subscription view and press unsubscribe to unsubscribe.
* Subscribe button
    * Subscribe a topic written in Topic input
* Broker address
    * MQTT broker name.
    
