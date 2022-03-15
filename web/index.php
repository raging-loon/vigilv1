<?php 
  $server = "localhost";
  $username = "NORAA";
  $password = "Pa@@w0rD";
  $conn = new mysqli($server, $username, $password, "NORAADB");
  if($conn->connect_error){
    die("Connection failed: " . $conn->connect_error);
  }

?>

<!DOCTYPE html>
  <head><title>NORAA Management</title></head>
  <body>
    <?php 
      $query = "SELECT * FROM arp_cache";
      $result = $conn->query($query);
      while($row = $result->fetch_assoc())
        echo "" . $row["ip_address"] . " -> " . $row["mac_address"]."\n";
      
    ?>
  </body>