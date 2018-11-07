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
        cc.log("onLoad...");
        this.values = [1, 2];
        this.label.string = this.text;
        this.label.string = this.values[0] + "," + this.values[1];
        this.enabled = true;
        this.schedule(function () {
            cc.log(this.label.string);
            this.label.string += "a";

        }, 5, 3, 1);

    },

    // called every frame
    update: function (dt) {
        // cc.log(dt);
    },
});
