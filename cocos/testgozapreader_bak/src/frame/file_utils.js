/**
* Created by zhaojm on 14/12/1.
*/
frame.fileUtils = {

  readTxtFile:function(filename){
      //cc.log('frame.fileUtils->readTxtFile, isNative=', cc.sys.isNative);
      if(cc.sys.isNative){
          return jsb.fileUtils.getStringFromFile(filename);
      }else{
          return cc.loader._loadTxtSync(filename);
      }
  },

  readTxtFileToJsonObj:function(filename){
      return JSON.parse(this.readTxtFile(filename));
  },

}

var test = function(){
    //frame.gameworld = new frame.GameWorld();
    var jsonObj = frame.fileUtils.readTxtFileToJsonObj('res/shilaimudongzuo.json');
    cc.log('jsonObj=', jsonObj);
};
//test();