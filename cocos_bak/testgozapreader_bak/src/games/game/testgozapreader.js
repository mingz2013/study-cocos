/**
 * Created by zhaojm on 14/12/2.
 */

var TestGozapReaderLayer = cc.Layer.extend({
    //sprite:null,
    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        /////////////////////////////
        //// 2. add a menu item with "X" image, which is clicked to quit the program
        ////    you may modify it.
        //// ask the window size
        var size = cc.winSize;

        // add a "close" icon to exit the progress. it's an autorelease object
        var closeItem = new cc.MenuItemImage(
            res.CloseNormal_png,
            res.CloseSelected_png,
            function () {
                cc.log("Menu is clicked!");

                //var animation = cc.animationCache.getAnimation('fenlie');
                //var animate = cc.Animate.create(animation);
                //cc.log(animation, animate);
                //this.gozapsprite.runAction(cc.repeatForever(animate));



                //var animation = cc.animationCache.getAnimation('fenlie');
                //var animate = frame.GozapAnimate.create(animation);
                //cc.log(animation, animate);
                //this.gozapsprite.runAction(cc.repeatForever(animate));

                //
                //this.gozapsprite.setSpriteFrame(cc.spriteFrameCache.getSpriteFrame('image43'));
                //
                //var framearr = [];
                //for(var i = 10; i < 27; i++){
                //    framearr.push(
                //        cc.AnimationFrame.create(
                //            cc.spriteFrameCache.getSpriteFrame('image' + i), 1, {x:200, y:200}
                //    ));
                //}
                //
                //cc.log(framearr);
                //
                //var anima = cc.Animation.createWithAnimationFrames(framearr, 0.2, 100);
                //
                ////this.gozapsprite.runAction(
                ////    cc.Animate.create(anima)
                ////);
                ////
                //this.gozapsprite.runAction(
                //    frame.GozapAnimate.create(anima)
                //);

            }, this);
        closeItem.attr({
            x: size.width - 20,
            y: 20,
            anchorX: 0.5,
            anchorY: 0.5
        });

        var menu = new cc.Menu(closeItem);
        menu.x = 0;
        menu.y = 0;
        this.addChild(menu, 1);

        ///////////////////////////////
        //// 3. add your codes below...
        //// add a label shows "Hello World"
        //// create and initialize a label
        //var helloLabel = new cc.LabelTTF("Hello World", "Arial", 38);
        //// position the label on the center of the screen
        //helloLabel.x = size.width / 2;
        //helloLabel.y = 0;
        //// add the label as a child to this layer
        //this.addChild(helloLabel, 5);
        //
        //// add "HelloWorld" splash screen"
        this.sprite = new cc.Sprite(res.HelloWorld_png);
        this.sprite.attr({
            x: size.width / 2,
            y: size.height/ 2
            //scale: 0.5,
            //rotation: 180
        });
        this.addChild(this.sprite, 0);
        //
        //this.sprite.runAction(
        //    cc.sequence(
        //        cc.rotateTo(2, 0),
        //        cc.scaleTo(2, 1, 1)
        //    )
        //);
        //helloLabel.runAction(
        //    cc.spawn(
        //        cc.moveBy(2.5, cc.p(0, size.height - 40)),
        //        cc.tintTo(2.5,255,125,0)
        //    )
        //);

        //this.gozapsprite = frame.GozapReader.readSpriteFromJsonFile('res/shilaimudongzuo.json');
        //
        //cc.log('gozapsprite=', this.gozapsprite);
        //
        //this.gozapsprite.attr({
        //    x: size.width / 2,
        //    y: size.height / 2
        //});
        //
        //this.addChild(this.gozapsprite);
        //
        //var animation = cc.animationCache.getAnimation('yidong2');
        //cc.log('animation=', animation);
        //var animate = frame.GozapAnimate.create(animation);
        //cc.log('animate=', animate);
        //this.gozapsprite.runAction(cc.repeatForever(animate));





        //var movieClip = frame.GozapMovieClip.create('res/shilaimudongzuo.json');
        //
        ////cc.log('movieClip=', movieClip);
        //
        //this.addChild(movieClip);
        //movieClip.setPosition(size.width / 2, size.height / 2);
        ////movieClip.setPosition(0, 0);
        //
        //movieClip.playSomeAction('待机2');
        //
        ////movieClip.runAction(
        ////    cc.MoveBy.create(10, cc.p(100,100))
        ////);

        var gozapSprite = frame.GozapSprite.createWithJsonFile('res/shilaimudongzuo.json');
        this.addChild(gozapSprite);
        gozapSprite.setPosition(size.width / 2, size.height / 2);
        //gozapSprite.playSomeActionByName('移动');
        gozapSprite.playSomeAction(cc.RepeatForever.create(frame.GozapAnimate.create(cc.animationCache.getAnimation('移动'))));
        return true;
    }
});

var TestGozapReaderScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new TestGozapReaderLayer();
        this.addChild(layer);
    }
});

