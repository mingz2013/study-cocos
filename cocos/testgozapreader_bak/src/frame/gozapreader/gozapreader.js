/**
 * Created by zhaojm on 14/12/1.
 */
frame.GozapReader = (function(){
    var parseJsonFile = function(jsonfile){

        var jsonObj = frame.fileUtils.readTxtFileToJsonObj(jsonfile) || {};
        if (jsonObj == {}) return null;


        var scale = jsonObj['scale'] || 1;
        var fileName = jsonObj['fileName'] || "";
        var clipping = jsonObj['clipping'] || {};
        var mcObjs = jsonObj['mcObjs'] || {};
        var imgArr = jsonObj['imgArr'] || [];

        var spriteModel = new frame.GozapSpriteModel();
        spriteModel.plistUrl = fileName;

        parseImgArr(imgArr, fileName);
        parseMCObj(mcObjs, 'root', spriteModel);

        return spriteModel;

    };

    var parseImgArr = function(imgArr, fileName){
        for (var i in imgArr) {
            if (imgArr[i]['size'] > 0) {
                var imgName = 'res/' + fileName + '/' + imgArr[i]['name'];

                    cc.spriteFrameCache.addSpriteFrames(
                    imgName + '.plist', imgName + '.png'
                );
            }
        }
    };

    var parseMCObj = function(mcObjs, objName, spriteModel){
        var mcObj = mcObjs[objName] || {};
        if(mcObj == {}) return;

        var frameLabels = mcObj['frameLabels'] || {};
        var screenH = mcObj['screenH'] || 640.00;
        var stageHeight = mcObj['stageHeight'] || 46.95;
        var layers = mcObj['layers'] || [];
        var direction = mcObj['direction'] || 1;
        var totalFrame = mcObj['totalFrame'] || 0;
        var frameTime = mcObj['frameTime'] || 60;
        var frameMoveObj = mcObj['frameMoveObj'] || {};

        spriteModel.frameMoveObj = frameMoveObj;

        if(layers == []) return null;
        var layer = layers[0];  // 先取第一层，试试

        spriteModel.defaultSpriteFrameName = layer[0]['libName']

        var animationFrameArray = [];
        var timelineIndex = 0;
        for(var i in layer){
            var keyframe = layer[i];

            var libName = keyframe['libName'];
            var frameNum = keyframe['frameNum'] || 0;
            var x = keyframe['x'] || 0;
            var y = keyframe['y'] || 0;

            while(frameNum >= 0){   // 至少一次

                var spriteframe = cc.spriteFrameCache.getSpriteFrame(libName);
                var userinfo = {
                    'position':cc.p(x, y),
                    'timelineIndex':timelineIndex
                };
                var animationframe = cc.AnimationFrame.create(spriteframe, 1, userinfo);

                animationFrameArray.push(animationframe);
                frameNum--;
                timelineIndex++;
            }
        }

        cc.assert(totalFrame == animationFrameArray.length, '数据有错误');



        for(var key in frameLabels) {

            var label = frameLabels[key];
            var framearray = [];
            var begin = label['begin'];
            var end = label['end'] || (totalFrame - 1);

            framearray = animationFrameArray.slice(begin, end + 1);

            var animation = cc.Animation.createWithAnimationFrames(framearray, frameTime / 1000, 1);
            cc.animationCache.addAnimation(animation, key);

            spriteModel.actionlist.push(key);
        }

    };

    var readSpriteFromJsonFile = function(jsonfile){
        return parseJsonFile(jsonfile);
    };

    return {
        'readSpriteFromJsonFile':readSpriteFromJsonFile,
    };


})();


var test = function(){
    frame.GozapReader.readSpriteFromJsonFile('res/shilaimudongzuo.json');
};
//test();