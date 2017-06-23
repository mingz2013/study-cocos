/**
 * Created by zhaojm on 14/12/2.
 */

cc.log('||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||');

cc.Animate.extend = cc.Class.extend;
frame.GozapAnimate = cc.Animate.extend({

    ctor:function (animation) {
        //cc.log("frame.GozapAnimate->ctor, animation=", animation);
        //cc.Animate.prototype.ctor.call(this, animation);
        //this._super(animation);

    },

    clone:function () {
        var action = new frame.GozapAnimate();
        this._cloneDecoration(action);
        action.initWithAnimation(this._animation.clone());
        return action;
    },

    /**
    * Called once per frame. Time is the number of seconds of a frame interval.
    * @param {Number} dt
    */
    update:function (dt) {
        dt = this._computeEaseTime(dt);
        // if t==1, ignore. Animation should finish with t==1
        if (dt < 1.0) {
            dt *= this._animation.getLoops();

            // new loop?  If so, reset frame counter
            var loopNumber = 0 | dt;
            if (loopNumber > this._executedLoops) {
                this._nextFrame = 0;
                this._executedLoops++;
            }

            // new t for animations
            dt = dt % 1.0;
        }

        var frames = this._animation.getFrames();
        var numberOfFrames = frames.length, locSplitTimes = this._splitTimes;
        for (var i = this._nextFrame; i < numberOfFrames; i++) {
            if (locSplitTimes[i] <= dt) {
                this.target.setSpriteFrame(frames[i].getSpriteFrame());

                var userinfo = frames[i].getUserInfo();

                cc.log(userinfo);

                this.target.setPosition(cc.p(
                    parseFloat(userinfo.position.x),
                    parseFloat(userinfo.position.y)
                ));

                this.target.getParent().onFrameUpdateEvent(userinfo.timelineIndex);

                this._nextFrame = i + 1;
            } else {
                // Issue 1438. Could be more than one frame per tick, due to low frame rate or frame delta < 1/FPS
                break;
            }
        }
    },

    reverse:function () {
        var locAnimation = this._animation;
        var oldArray = locAnimation.getFrames();
        var newArray = [];
        cc.arrayVerifyType(oldArray, cc.AnimationFrame);
        if (oldArray.length > 0) {
            for (var i = oldArray.length - 1; i >= 0; i--) {
                var element = oldArray[i];
                if (!element)
                    break;
                newArray.push(element.clone());
            }
        }
        var newAnim = new cc.Animation(newArray, locAnimation.getDelayPerUnit(), locAnimation.getLoops());
        newAnim.setRestoreOriginalFrame(locAnimation.getRestoreOriginalFrame());
        var action = new frame.GozapAnimate(newAnim);
        this._cloneDecoration(action);
        this._reverseEaseList(action);

        return action;
    },

});

frame.gozapAnimate = function (animation) {
    return new frame.GozapAnimate(animation);
};

frame.GozapAnimate.create = frame.gozapAnimate;

cc.log('||||||||||||||||||||||||||||||||||||||||||||||||||||');