#pragma once

#include "ofMain.h"
#include "ofVbo.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofCamera cam; // カメラ
    ofVec3f center; // カメラ方向
    
    ofImage texture; // パーティクルに貼るテクスチャイメージ
    
    // マウス追跡パーティクル
    ofVbo mouseParticle;
    ofVec3f mpVerts;        // 頂点座標情報
    ofFloatColor mpColor;   // 頂点色情報
    
    // 描画されるパーティクル
    ofVbo drownParticle;
    vector<ofVec3f> dpVerts;        // 頂点座標情報
    vector<ofFloatColor> dpColor;   // 頂点色情報
    vector<ofVec3f> dpVels;         // 移動速度
};
