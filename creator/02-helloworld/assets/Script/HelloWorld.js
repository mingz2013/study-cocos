cc.Class({
    extends: cc.Component,

    properties: {
        label: {
            default: null,
            type: cc.Label
        },
        // defaults, set visually when attaching this script to the Canvas
        text: 'Hello, World!',
        values: [cc.Integer],
    },

    // use this for initialization
    onLoad: function () {
        this.label.string = this.text;
//         this.values = [1];
    },

    // called every frame
    update: function (dt) {

    },
});
