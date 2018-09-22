<?php
//database settings
$database = "DATABASE NAME"
$db_with_coll = $database + "." + "COLLECTION NAME"


//end database settings

echo("\n\n");

if ($_POST['temp'] || $_POST['humid'] || $_POST['ident']) {
    echo "  TEMP: ". $_POST['temp'];
    echo "  HUMID: ". $_POST['humid'];
    echo "  IDENT: ". $_POST['ident'];
    $t=time();
    echo("   ". $t. "   ");
    echo(date("Y-m-d",$t));
    echo("\n");
    }


//mongodb storing
try {
    $mng = new MongoDB\Driver\Manager("mongodb://localhost:27017");

    $stats = new MongoDB\Driver\Command(["dbstats" => 1]);
    $res = $mng->executeCommand($database, $stats);

    if ($_POST['ident']) {

    $bulk = new MongoDB\Driver\BulkWrite;

    $document = [
            "_id" => new MongoDB\BSON\ObjectID,
            "ident" => $_POST['ident'],
            "temp" => $_POST['temp'],
            "humid" => $_POST['humid'],
            "time" => $t
    ];

    $bulk->insert($document);
    $mng->executeBulkWrite($database_with_coll, $bulk);
    }

    $stats = current($res->toArray());
    print_r($stats);
} catch (MongoDB\Driver\Exception\Exception $e) {
    $filename = basename(__FILE__);

    echo "The $filename script has experienced an error.\n"; 
    echo "It failed with the following exception:\n";

    echo "Exception:", $e->getMessage(), "\n";
    echo "In file:", $e->getFile(), "\n";
    echo "On line:", $e->getLine(), "\n";    
}

exit();
?>
