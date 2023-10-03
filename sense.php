<?php
class pms{
 public $link='';
 function __construct($state, $s_no){
  $this->connect();
  $this->storeInDB($state, $s_no);
 }
 
 function connect(){
  $this->link = mysqli_connect('localhost','root','') or die('Cannot connect to the DB');
  mysqli_select_db($this->link,'ultra') or die('Cannot select the DB');
 }
 
 function storeInDB($state, $s_no){
  $query = "update distance set state='".$state."' where S_No='".$s_no."'";
  $result = mysqli_query($this->link,$query) or die('Errant query:  '.$query);
 }
 
}
if($_GET['state'] != '' and $_GET['s_no'] != ''){
 $pms=new pms($_GET['state'],$_GET['s_no']);
}
?>