<?php
  2     if (isset($_GET['ledOn'])) {
  3         $ret = shell_exec("/home/pi/PHP_LEDON 2>&1");
  4         echo $ret;
  5     }
  6     else if (isset($_GET['ledOff'])) {
  7         $ret = shell_exec("/home/pi/PHP_LEDOFF 2>&1");
  8         echo $ret;
  9     }
 10     else if (isset($_GET['light'])) {
 11         $ret = shell_exec("/home/pi/PHP_LIGHT 2>&1");
 12    $ret_int = intval($ret);
 13    echo $ret_int;
 14     }
 15     else if (isset($_GET['aa'])) {
 16
 17         $ret = shell_exec('/home/pi/aa 2>&1');
 18
 19         echo $ret;
 20
 21     }
 22     else {
 23         echo "This is remoteC.php. You entered wrong parameter.";
