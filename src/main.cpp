#include <Arduino.h>
#include <math.h>

#include "option.hpp"
#include "sensorCheck.hpp"
#include "degCalculation.hpp"

#define IRValueCheck 0 // 1: センサの値チェック 0: 角度を出す コメントアウト:実行しない


void setup()
{
  Serial.begin(115200);

  serialStart();
}

void loop()
{
  #ifdef IRValueCheck // ====IRセンサ=========================================
  #if IRValueCheck
  sensorCheck();
  #else
  degCalculation();
  #endif
  #endif

  Serial.println();

  delay(100);
}

/* ==変数・定数・関数一覧==
IR_FIRST_PIN = IRの最初のピン番号
IR_LAST_PIN = IRの最後のピン番号
IR_COUNT = IRセンサの総数
NOT_BOLL_FOUND = ボールが見つからないと判断する最小の仮値

irValue[] = その時々のセンサの値の格納庫。[]の中の数はピン番号
ball_found = ボールがあると、trueになる。ボールがないとfalseとなり、プログラムの最初に戻る。デフォルトはfalse
theta = ボールの角度。θ

deg_radian() = ()の中のピン番号と接続してあるセンサのIR_FIRST_PINを0°とした向いている角度。
あとはまあフィーリングで考えて。
== ==*/

