#include <Arduino.h>
#include <math.h>

#include "option.hpp"
#include "sensorCheck.hpp"
#include "degCalculation.hpp"

#include "moveAverage.hpp"

#define IRValueCheck 0 // 1: センサの値チェック 0: 角度を出す コメントアウト:実行しない

EMAfilter sensors[8];
IRcalculation IRcal;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  // for (int i = 0; i < IR_COUNT; i++) {
  //   sensors[i].EMA_init(0.2f);
  // }
  // serialStart();

  IRcal.IRinit();
}

void loop()
{
  #ifdef IRValueCheck // ====IRセンサ=========================================
  #if IRValueCheck
  sensorCheck();
  #else
  IRcal.degCalculation();
  #endif
  #endif

  Serial.println();

  delay(1);
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

