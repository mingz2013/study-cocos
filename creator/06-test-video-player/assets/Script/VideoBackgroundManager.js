// Learn cc.Class:
//  - [Chinese] https://docs.cocos.com/creator/manual/zh/scripting/class.html
//  - [English] http://docs.cocos2d-x.org/creator/manual/en/scripting/class.html
// Learn Attribute:
//  - [Chinese] https://docs.cocos.com/creator/manual/zh/scripting/reference/attributes.html
//  - [English] http://docs.cocos2d-x.org/creator/manual/en/scripting/reference/attributes.html
// Learn life-cycle callbacks:
//  - [Chinese] https://docs.cocos.com/creator/manual/zh/scripting/life-cycle-callbacks.html
//  - [English] https://www.cocos2d-x.org/docs/creator/manual/en/scripting/life-cycle-callbacks.html

cc.Class({
    extends: cc.Component,

    properties: {
        // foo: {
        //     // ATTRIBUTES:
        //     default: null,        // The default value will be used only when the component attaching
        //                           // to a node for the first time
        //     type: cc.SpriteFrame, // optional, default is typeof default
        //     serializable: true,   // optional, default is true
        // },
        // bar: {
        //     get () {
        //         return this._bar;
        //     },
        //     set (value) {
        //         this._bar = value;
        //     }
        // },

        // videoPlayer:cc.VideoPlayer,

    },

    // LIFE-CYCLE CALLBACKS:

    onLoad () {




    },

    start () {

        let video = this.node.getComponent(cc.VideoPlayer);
        // video.active = true;
        video.enabled = true;


    },

    // update (dt) {},

    onVideoPlayerEvent (sender, event) {
        cc.log("=====> event: ", event);
        cc.log("=====eventType: ", JSON.stringify(cc.VideoPlayer.EventType));
        // this.statusLabel.string = 'Status: ' + getStatus(event);
        // if (event === cc.VideoPlayer.EventType.CLICKED) {
        //     if (this.videoPlayer.isPlaying()) {
        //         this.videoPlayer.pause();
        //     } else {
        //         this.videoPlayer.play();
        //     }
        // }
        if (event === cc.VideoPlayer.EventType.READY_TO_PLAY || event === cc.VideoPlayer.EventType.META_LOADED) {
            // this.controlButtons.active = true;
            // this.playVideoArea.active = true;
            let video = this.node.getComponent(cc.VideoPlayer);
            video.play();

        } else if (event === cc.VideoPlayer.EventType.STOPPED || event === cc.VideoPlayer.EventType.COMPLETED) {
            let video = this.node.getComponent(cc.VideoPlayer);
            video.play();
        }
        // else if (event === cc.VideoPlayer.EventType.PLAYING) {
        //     this.playVideoArea.active = false;
        // }
    },


});
