<?php
function load_cart()
{
    if(!empty($_COOKIE['cart'])) $cart=unserialize($_COOKIE['cart']);
    else $cart = array();
    return $cart;
}
?>

<?php
require_once("db.inc");
function query_item($ID) {
 global $db;
 $stmt = $db->prepare("select * from products where ID=?");
 $stmt->bind_param("i", $ID);
 $stmt->execute();
 if($result = $stmt->get_result()) {
 if($row = $result->fetch_object()) {
 return $row;
 }
 }
 return null;
}
?>

<?php
function show_cart($cart)
{
 print "<table>";
 print "<tr>";
 print "<th></th>";
 print "<th>Product</th>";
 print "<th>Qty</th>";
 print "<th></th>";
 print "<th>Unit</th>";
 print "<th>Price</th>";
 print "</tr>";
$total = 0;
foreach($cart as $ID=>$qty) $total+= show_item($ID, $qty);
print "<tr><td colspan='5' align='right'>Total</td><td>";
print "<b>$".number_format($total,2)."</b>"; 
print "</td></tr>";
print "<tr><td colspan='6' align='center'>";
print "</td></tr>";
print "</table>";
}

function show_item($ID, $qty) {
 $item = query_item($ID);
 if($item == null) return 0;
 print "<tr>";
 print "<td><a href='cart.html?ID=$ID&qty=0'><i
 class='fa fa-trash'></i></a></td>";
 print "<td><b>".$item->Name."</b></td>";
 print "<form action='cart.html'>";
 print "<input type='hidden' name='ID' value='$ID'>";
 print "<td><input type='text' name='qty' value='$qty'></td>";
 print "<td><button type='submit'>Update</button></td>";
 print "</form>";
 print "<td>$".$item->Price."</td>";
 print "<td>$".number_format($qty*$item->Price,2)."</td>";
 print "</tr>";
 return $qty*$item->Price;
}
?>
