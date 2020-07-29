#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // 画面設定
    ofBackground(0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    
    // カメラ設定
    cam.setPosition(0.0, 0.0, 2000.0);
    cam.lookAt(center);
    cam.setFov(75);
    center.set(0.0, 0.0, 0.0);
    
    // テクスチャー画像を設定
    ofDisableArbTex();
    texture.load("particle32.png");
}

//--------------------------------------------------------------
void ofApp::update(){
    // パーティクルの座標を更新
    float t   = (ofGetElapsedTimef()) * 0.9f;
    float div = 250.0;
    for(int i = 0; i < dpVels.size(); i++){
        // ノイズを生成し移動速度に
        ofVec3f vec(ofSignedNoise(t, dpVerts[i].y/div, dpVerts[i].z/div),
                    ofSignedNoise(dpVerts[i].x/div, t, dpVerts[i].z/div),
                    ofSignedNoise(dpVerts[i].x/div, dpVerts[i].y/div, t));
        
        vec *= 0.3f;
        
        // 速度をもとにパーティクル位置を更新
        dpVels[i] += vec;
        dpVerts[i] += dpVels[i];
        dpVels[i]  *= 0.94f;
    }
    
    // VBOの更新
    mouseParticle.setVertexData(&mpVerts, 1, GL_DYNAMIC_DRAW);
    mouseParticle.setColorData(&mpColor, 1, GL_DYNAMIC_DRAW);
    
    drownParticle.setVertexData(dpVerts.data(), dpVerts.size(), GL_DYNAMIC_DRAW);
    drownParticle.setColorData(dpColor.data(), dpColor.size(), GL_DYNAMIC_DRAW);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);
    
    cam.begin();
    
    // パーティクル描画設定
    glDepthMask(GL_FALSE);
    ofEnablePointSprites();
    texture.getTexture().bind();
    
    // パーティクルのZ軸の位置によって大きさを変化させる
    static GLfloat distance[] = { 0.0, 0.0, 1.0 };
    glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, distance);
    glPointSize(30000);
    
    // パーティクルを描画
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    mouseParticle.draw(GL_POINTS, 0, 1); // マウス追跡パーティクル
    drownParticle.draw(GL_POINTS, 0, dpVerts.size()); // 描画されるパーティクル
    
    texture.getTexture().unbind();
    ofDisablePointSprites();
    glDepthMask(GL_TRUE);
    
    cam.end();
    
    ofPopMatrix();
    
    // ログを表示
    ofSetColor(255, 255, 255);
    string info = ofToString(ofGetFrameRate(), 2) + "\n";
    info += "Particle Count: 1 + " + ofToString(dpVerts.size()) + "\n";
    ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    // マウス追跡パーティクル
    mpVerts.set(x - ofGetWidth()/2, -y + ofGetHeight()/2, 1500);
    mpColor.set(1, 1, 1, 1);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    // 描画されるパーティクル
    // 頂点座標の追加
    ofVec3f mousePoint(x - ofGetWidth()/2, -y + ofGetHeight()/2, 1500);
    dpVerts.push_back(mousePoint);
    
    // 色情報の追加
    ofFloatColor clr(1, 1, 1, 0.7);
    dpColor.push_back(clr);
    
    // 移動速度情報の追加
    ofVec3f vels(ofRandomf(), -1.0, ofRandomf());
    dpVels.push_back(vels);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
