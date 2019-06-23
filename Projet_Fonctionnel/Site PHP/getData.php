<?php

define("db_host","localhost");
define("db_user","Eixa@localhost");
define("db_password","Eixa6");
define("db_name","METEO");
$db_instance = new PDO("mysql:host=" . db_host . ";dbname=" . db_name . ";charset=utf8", db_user, db_password);
$db_instance->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
$db_instance->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);

$prepared_query = $db_instance->prepare("SELECT * FROM Anemometre;");
$prepared_query->execute();
$query_results = $prepared_query->fetchAll(PDO::FETCH_ASSOC);
?>
