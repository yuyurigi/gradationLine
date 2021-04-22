#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetBackgroundAuto(true);

    buttonPos = 2;
    count = -1;
    vertexNum = 0;
    
    setGui(); //gui
}

//--------------------------------------------------------------
void ofApp::update(){
    if(polylines.size()>0 && vertexNum > 2&& dist < 30){
        circle.update();
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(backColor);
    
    checkLineCap();
    checkLineJoin();
    
    if((count>=0)&&(vertexNum>0)){
        polylines[count].setLineWidth(lineWidth);
        polylines[count].setWireframe(bWire);
        polylines[count].setGradation(bGradation);
        polylines[count].setLineCap(cap);
        polylines[count].setLineJoin(join);
    }
    
    for(int i = 0; i < polylines.size(); i++){
        polylines[i].setColor(color1, color2, color3);
        polylines[i].draw();
    }
    
    
    if(polylines.size()>0 && vertexNum > 2){
        glm::vec2 firstPos = circle.getFirstPos();
        dist = ofDist(firstPos.x, firstPos.y, mouseX, mouseY);  
        if(dist < 30){
            circle.draw();
        }
    }
    
    if( !bHide ) gui.draw();
    
    cout << "count:" << count << endl;
    cout << "vertexnum:" << vertexNum << endl;
    cout << "buttonPos:" << buttonPos << endl;
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // s : スクリーンショット
    // h : gui表示/非表示
    // c : 画面をクリアー
    // r : パラメーターをリセット
    // 1 : カラー１
    // 2 : カラー２
    // 3 : カラー３
    // 4 : カラー４
    // 5 : カラー５
    // delete, backspace : 頂点をひとつ消す
    switch(key){
        case 's'://screenshot
        case 'S':
            myImage.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
            myImage.save(ofGetTimestampString("%Y%m%d%H%M%S")+"##.png");
            break;
        case 'h': //gui display/ !display
        case 'H':
            bHide = !bHide;
            break;
        case 'c': //clear
        case 'C':
            polylines.clear();
            count = -1;
            vertexNum = 0;
            buttonPos = 2;
            break;
        case 'r'://reset parameter
        case 'R':
            lineWidth = 30;
            backColor = ofColor(245, 198, 200);
            color1 = ofColor(237, 98, 134); //濃いピンク
            color2 = ofColor(246, 209, 106); //黄色
            color3 = ofColor(129, 196, 226); //水色
            bWire = false;
            bGradation = true;
            break;
        case '1': //color set 1
            backColor = ofColor(245, 198, 200);
            color1 = ofColor(237, 98, 134); //濃いピンク
            color2 = ofColor(246, 209, 106); //黄色
            color3 = ofColor(129, 196, 226); //水色
            break;
        case '2': //color set 2
            backColor = ofColor(245, 198, 200);
            color1 = ofColor(237, 98, 134); //濃いピンク
            color2 = ofColor(246, 209, 106); //黄色
            color3 = ofColor(242, 180, 107); //オレンジ
            break;
        case '3': //color set 3
            backColor = ofColor(239, 243, 250);
            color1 = ofColor(172, 217, 212); //緑
            color2 = ofColor(138, 178, 223); //青
            color3 = ofColor(223, 221, 25); //黄緑
            break;
        case '4': //color set 4
            backColor = ofColor(135, 201, 233); //水色
            color1 = ofColor(229, 145, 177); //ピンク
            color2 = ofColor(238, 233, 224); //白
            color3 = ofColor(163, 145, 255); //緑
            break;
        case '5': //color set 5
            backColor = ofColor(56, 68, 92); //紺
            color1 = ofColor(201, 235, 228); //水色
            color2 = ofColor(248, 205, 200); //ピンク
            color3 = ofColor(68, 112, 126); //緑
            break;
        case OF_KEY_DEL: //頂点をひとつ消す
        case OF_KEY_BACKSPACE:
            deletePos();
            break;
    }
}

//--------------------------------------------------------------
void ofApp::deletePos(){
    //線を引いてる途中のとき----------------------------------------
    if (vertexNum > 1){
            polylines[count].deletePoint(1);
            vertexNum -= 1;
    //頂点が全体でひとつしかないとき----------------------------------
    }else if ((vertexNum == 1) && (count == 0)){
        polylines.clear();
        count = -1;
        vertexNum = 0;
        buttonPos = 2;
    //頂点がひとつだけのとき-----------------------------------------
    }  else if ((vertexNum == 1) && (count > 0)) {
        polylines.pop_back();
        count -= 1;
        vertexNum = 0;
        buttonPos = 2;
        glm::vec2 firstPos = polylines[count].getFirstPos();
        circle.setup(firstPos.x, firstPos.y, 30);
    //前の図形が閉じてるとき------------------------------------------
    } else if((vertexNum == 0)&&(count>=0)){
        vertexNum = polylines[count].getPosNum();
        if(vertexNum == 1){ //頂点がひとつだけのとき
            polylines.pop_back();
            count -= 1;
            if (count == -1) {
                vertexNum = 0;
                buttonPos = 2;
            } else if (count > -1){
                glm::vec2 firstPos = polylines[count].getFirstPos();
                circle.setup(firstPos.x, firstPos.y, 30);
                vertexNum = 0;
                buttonPos = 2;
            }
        } else if (vertexNum > 1){ //頂点が２つ以上あるとき
            if (polylines[count].getClose()){ //線が閉じてるとき
                polylines[count].deletePoint(2);
                polylines[count].setClose(false);
                glm::vec2 firstPos = polylines[count].getFirstPos();
                circle.setup(firstPos.x, firstPos.y, 30);
                buttonPos = 0;
                vertexNum -= 1;
            } else { //閉じてないとき
                polylines[count].deletePoint(1);
                glm::vec2 firstPos = polylines[count].getFirstPos();
                circle.setup(firstPos.x, firstPos.y, 30);
                buttonPos = 0;
                vertexNum -= 1;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    //マウス（左）：頂点を追加する（最初の頂点に表示される丸枠内を押したら図形を閉じる）
    //マウス（右）：いま描いてる図形を終わらせる
    
    //button (left 0, center 1, right 2)
    if (button == 0) { //マウス（左）押したとき
        //円を押した時、図形を閉じる
        if(polylines.size()>0 && vertexNum > 2 && dist < 30){
            polylines[count].setClose(true);
            buttonPos = 2;
            vertexNum = 0;
        } else {
            
        vertexNum += 1; //頂点数を増やす
        if(buttonPos != button){ //最初のクリック、右押したあと左押したとき
            count += 1;
            //新しい図形を描き始める
            Polyline p;
            p.setLineWidth(lineWidth);
            p.setColor(color1, color2, color3);
            p.setPos(glm::vec2(mouseX, mouseY));
            p.setLineCap(cap); //0:butt, 1:round, 2:square
            p.setLineJoin(join); //0:miter, 1:bevel, 2:round
            p.setWireframe(bWire);
            p.setGradation(bGradation);
            polylines.push_back(p);
            //書き始めの位置に円を描く
            
            if(vertexNum == 1){
                circle.setColor(ofColor(255, 255, 255));
                circle.setup(mouseX, mouseY, 30);
            }
            
        } else {
            //図形に線を追加していく
            polylines[count].setPos(glm::vec2(mouseX, mouseY));
        }
        buttonPos = 0;
        }
    }
    
    if (button == 2){ //マウス（右）押したとき
        //今描いてる図形を終わらせる
        if (vertexNum > 0) {
            buttonPos = 2;
            vertexNum = 0;
        }
    }

}
//--------------------------------------------------------------
void ofApp::setGui(){
    bHide = false;
    //gui
    parameters.setName("settings");
    parameters.add(lineWidth.set("lineWidth", 20, 1, 100));
    parameters.add(bWire.set("wire", false));
    parameters.add(bGradation.set("gradation", true));
    linecap.setName("linecap");
    linecap.add(capParameter[0].set("butt", false));
    linecap.add(capParameter[1].set("round", true));
    linecap.add(capParameter[2].set("square", false));
    parameters.add(linecap);
    linejoin.setName("linejoin");
    linejoin.add(joinParameter[0].set("miter", false));
    linejoin.add(joinParameter[1].set("bevel", false));
    linejoin.add(joinParameter[2].set("round_", true));
    parameters.add(linejoin);
    color.setName("color");
    color.add(backColor.set("background", ofColor(245, 198, 200), ofColor(0,0), ofColor(255, 255))); //ピンク
    color.add(color1.set("color1",ofColor(237, 98, 134),ofColor(0,0),ofColor(255,255))); //濃いピンク
    color.add(color2.set("color2",ofColor(246, 209, 106),ofColor(0,0),ofColor(255,255))); //黄色
    color.add(color3.set("color3",ofColor(129, 196, 226),ofColor(0,0),ofColor(255,255))); //水色
    parameters.add(color);
    
    gui.setup(parameters);
    
    setLineCap();
    setLineJoin();
}
//--------------------------------------------------------------
void ofApp::setLineCap(){
    //bool false:0 true:1
    check[0] = false;
    check[1] = false;
    check[2] = false;
    
    for (int i = 0; i < 3; i++) {
        if(capParameter[i] == true){
            check[i] = true;
        }
    }
    
    for (int i = 0; i < 3; i++) {
        if(check[i] == true){
            cap = i;
        }
    }
}
//--------------------------------------------------------------
void ofApp::checkLineCap(){
    bool check2[3];
    for (int i = 0; i < 3; i++) {
        if (capParameter[i] == true) {
            check2[i] = true;
        } else if (capParameter[i] == false){
            check2[i] = false;
        }
    }
    
    for (int i = 0; i < 3; i++) {
        if(check[i] != check2[i]){
            if((check[i]==false) && (check2[i]==true)){
                cap = i;
            } else if ((check[i]==true) && (check2[i]==false) && (check2[(i+1)%3]==false) && (check2[(i+2)%3]==false)){
                cap = i;
            }
        }
    }
    
    if (cap == 0) {
        capParameter[0] = true;
        capParameter[1] = false;
        capParameter[2] = false;
    } else if (cap == 1) {
        capParameter[0] = false;
        capParameter[1] = true;
        capParameter[2] = false;
    } else if (cap == 2){
        capParameter[0] = false;
        capParameter[1] = false;
        capParameter[2] = true;
    }
    
    for (int i = 0; i < 3; i++) {
        check[i] = check2[i];
    }
    
}
//--------------------------------------------------------------
void ofApp::setLineJoin(){
    //bool false:0 true:1
    jcheck[0] = false;
    jcheck[1] = false;
    jcheck[2] = false;
    
    for (int i = 0; i < 3; i++) {
        if(joinParameter[i] == true){
            jcheck[i] = true;
        }
    }
    
    for (int i = 0; i < 3; i++) {
        if(jcheck[i] == true){
            join = i;
        }
    }
}
//--------------------------------------------------------------
void ofApp::checkLineJoin(){
    bool jcheck2[3];
    for (int i = 0; i < 3; i++) {
        if (joinParameter[i] == true) {
            jcheck2[i] = true;
        } else if (joinParameter[i] == false){
            jcheck2[i] = false;
        }
    }
    
    for (int i = 0; i < 3; i++) {
        if(jcheck[i] != jcheck2[i]){
            if((jcheck[i]==false) && (jcheck2[i]==true)){
                join = i;
            } else if ((jcheck[i]==true) && (jcheck2[i]==false) && (jcheck2[(i+1)%3]==false) && (jcheck2[(i+2)%3]==false)){
                join = i;
            }
        }
    }
    
    if (join == 0) {
        joinParameter[0] = true;
        joinParameter[1] = false;
        joinParameter[2] = false;
    } else if (join == 1) {
        joinParameter[0] = false;
        joinParameter[1] = true;
        joinParameter[2] = false;
    } else if (join == 2){
        joinParameter[0] = false;
        joinParameter[1] = false;
        joinParameter[2] = true;
    }
    
    for (int i = 0; i < 3; i++) {
        jcheck[i] = jcheck2[i];
    }
    
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
