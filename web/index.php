<?php 
  $server = "localhost";
  $username = "NPSI";
  $password = "Pa@@w0rD";
  $conn = new mysqli($server, $username, $password, "NPSIDB");
  if($conn->connect_error){
    die("Connection failed: " . $conn->connect_error);
  }
?>

<!DOCTYPE html>
  <head><title>NPSI Management</title></head>
  <body>
      
  
  </body>