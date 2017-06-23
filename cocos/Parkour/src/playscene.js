/**
 * Created by zhaojm on 15/3/19.
 */
var PlayScene = cc.Scene.extend({
    //space:null,

    onEnter:function(){
        this._super();
        //this.initPhysics();

        this.playLayer = new PlayLayer();
        this.addChild(this.playLayer);

        //this.scheduleUpdate();
    },



    //update:function(dt){
    //    //this.space.step(dt);    // 这一步是必须的
    //
    //},

});
var PlayLayer = cc.Layer.extend({
    space:null,

    ctor:function(){
        this._super();

        this.initPhysics();
        //add three layer in the right order
        this.backgroundLayer = new BackgroundLayer();
        this.addChild(this.backgroundLayer);
        this.animationLayer = new AnimationLayer(this.space);
        this.addChild(this.animationLayer);
        this.addChild(new StatusLayer());

        this.scheduleUpdate();
    },

    // init space of chipmunk
    initPhysics:function() {
        //1. new space object
        this.space = new cp.Space();
        //2. setup the  Gravity
        this.space.gravity = cp.v(0, -350);

        // 3. set up Walls
        var wallBottom = new cp.SegmentShape(this.space.staticBody,
            cp.v(0, g_groundHeight),// start point
            cp.v(4294967295, g_groundHeight),// MAX INT:4294967295
            0);// thickness of wall
        this.space.addStaticShape(wallBottom);
    },



    update:function(dt){
        this.space.step(dt);    // 这一步是必须的

        var eyeX = this.animationLayer.getEyeX();

        this.setPosition(cc.p(-eyeX,0));
    },


});