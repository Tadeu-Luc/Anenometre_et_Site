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



<div class="container">
<html lang="fr" dir="ltr">
    <head>
      <meta charset="utf-8">
      <title>Station Météo Eixa6 Informatique</title>
    </head>
    <body>
      <h1>Station Météo Eixa6 Informatique</h1>
            <img src="ImageEixa.png"
           width="250"
           height="250"
           align="right">
      <br>
      <h2> 
        <span style="text-decoration: underline;">
          Données recensées                                     
        </span>
      </h2>
    <div class="panel panel-default">
        <div class="panel-heading">
           
            <a href="Test.php" class="btn btn-success pull-right">Météo Eixa6 Informatique</a>
            <p>Vitesse:   <?php echo $query_results{0}{"Vitesse"};?></p> <!--récuperation des données Vitesse et mise dans l'html-->
            <p>Angle:   <?php echo $query_results{0}{"Angle"};?></p> <!--récuperation des données Vitesse et mise dans l'html-->
            <p>Direction:   <?php echo $query_results{0}{"Direction"};?></p> <!--récuperation des données Vitesse et mise dans l'html-->
            <p>Type de temps:   <?php echo $query_results{0}{"Typedetemps"};?></p> <!--récuperation des données Vitesse et mise dans l'html-->
            <p>Date et heure:   <?php echo $query_results{0}{"Heure"};?></p> <!--récuperation des données Vitesse et mise dans l'html-->
      
      <button type="submit">Actualiser les informations</button>
        </div>  
    </body>

