/**
 * Created by zhaojm on 15/3/19.
 */
var BackgroundLayer = cc.Layer.extend({
    backgroundImgList:null,


    backgroundList : null,


    ctor:function () {
        this._super();
        this.backgroundList = [];

        var size = cc.winSize;




        this.backgroundImgList = [res.playBG_png];


        for(;;){
            var w = this.addOneBackground();
            if( this.backgroundList.length * w >= size.width){
                break;
            }
        }

        this.scheduleUpdate();
    },


    update:function(dt){
        var eyeX = this.parent.animationLayer.getEyeX();

        // 判断背景删除和创建
        while(true){

            if(this.backgroundList[0].getPositionX() + this.backgroundList[0].getContentSize().width <= eyeX){
                //cc.log('removeBackground');
                this.removeChild(this.backgroundList[0]);

                this.backgroundList.splice(0, 1);

            }else{
                break;
            }
        }
        if(this.backgroundList[this.backgroundList.length - 1].getPositionX() + this.backgroundList[this.backgroundList.length - 1].getContentSize().width  -eyeX <= cc.winSize.width + 10){
            this.addOneBackground();
        }


    },


    addOneBackground:function(){
        //cc.log('addOneBackground');

        var bg = null;
        if(this.backgroundList.length == 0){

            bg = this.createBackgroundByIndex(0);

            bg.setPosition(cc.p(0, 0));

        }else{

            var lastBackground = this.backgroundList[this.backgroundList.length - 1];
            var lastIndex = lastBackground.backgroundImgIndex;
            lastIndex = (lastIndex + 1) % this.backgroundImgList.length;
            bg = this.createBackgroundByIndex(lastIndex);
            bg.setPosition(cc.p(lastBackground.getPositionX() + lastBackground.getContentSize().width , 0));
        }
        this.addChild(bg, 1);
        this.backgroundList.push(bg);


        return bg.getContentSize().width;
    },

    createBackgroundByIndex:function(index){

        var bg = new cc.Sprite(this.backgroundImgList[index]);

        bg.setAnchorPoint(cc.p(0, 0));
        bg.backgroundImgIndex = index;
        return bg;
    },




});