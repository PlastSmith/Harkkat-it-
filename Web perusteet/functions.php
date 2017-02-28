<?php

function tarkistaYhteys($conn, $sql) {
    if (!mysqli_query($conn, $sql)) {
        echo "Error: " . $sql . " " . mysqli_error($conn);
    } else {
        //echo $sql . " yhdistys onnistui <br>";
    }
}

function MinMaxTuuliAsetettu() {
    if ((is_numeric($_REQUEST['MinTuulennopeus'])) && (is_numeric($_REQUEST['MaxTuulennopeus']))) {
        return true;
    } else {
        return false;
    }
}

function MinMaxLampoAsetettu() {
    if ((is_numeric($_REQUEST['MinLampotila']) ) && (is_numeric($_REQUEST['MaxLampotila']))) {
        return true;
    } else {
        return false;
    }
}

function PaivamaaraAsetettu() {
    if ((isset($_REQUEST['alkupvm']) && !empty($_REQUEST['alkupvm'])) && (isset($_REQUEST['loppupvm']) && !empty($_REQUEST['loppupvm']))) {
        return true;
    } else {
        return false;
    }
}

function tilastokyselyRajoilla($conn, $tilastoKyselynTulokset) {
    
}

?>