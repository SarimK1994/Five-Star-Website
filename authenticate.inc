<?php
session_start();
if(!empty($_POST['user']) && !empty($_POST['pass'])) {
 $username = strtolower(trim($_POST['user']));
 $password = trim($_POST['pass']);
 if($username == 'admin' && $password == '123qwe')
 $_SESSION['user'] = 'admin';
 else
 $_SESSION['user'] = null;
}
if(!empty($_GET['logoff'])) $_SESSION['user'] = null;
if(empty($_SESSION['user'])) {
 require_once('redirect.inc');
 redirect('login.html');
}
?>