<?php

$host_db = "127.0.0.1";
$user_db = "root";
$password_db ="admin";
$db_name = "Fi-city";
$tbl_name = "temperature";
$data=array();
$conexion = mysqli_connect($host_db,$user_db, $password_db,$db_name) or die("Cannot Connect to DataBase");
try{
//$query = "SELECT INTENSIDAD, POTENCIA FROM sensores ORDER BY TIME DESC LIMIT 1";
$query = "SELECT data as TEMPERATURA from temperature";

$resultado = mysqli_query($conexion,$query);

if(mysqli_num_rows($resultado) == 0){
	$error = "No exite ningun dato";
	echo $error;
}
else{
	while ($row= mysqli_fetch_array($resultado, 1)) {
	$temp = $row['TEMPERATURA'] * 1.0;
	}
	
	$data[] = array('TEMPERATURA' => ($temp));
	echo json_encode($data);
	}
}
catch(Exception $e){
	die($error);
	$error = "error";
	echo $error;
}

?>