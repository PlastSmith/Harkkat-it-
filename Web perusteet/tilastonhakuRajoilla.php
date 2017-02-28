<?php
require_once("functions.php");

if (MinMaxLampoAsetettu() && MinMaxTuuliAsetettu() && PaivamaaraAsetettu()) {
        $tilastoKysely = "SELECT MIN(tuulennopeus1), MIN(tuulennopeus2), MIN(tuulensuunta1), MIN(tuulensuunta2), MIN(sademaara1), MIN(sademaara2), MIN(ulkolampotila1), MIN(ulkolampotila2), MIN(ulkoilmankosteus), MIN(sisailmankosteus), MIN(ilmanpaine),
                            MAX(tuulennopeus1), MAX(tuulennopeus2), MAX(tuulensuunta1), MAX(tuulensuunta2), MAX(sademaara1), MAX(sademaara2), MAX(ulkolampotila1), MAX(ulkolampotila2), MAX(ulkoilmankosteus), MAX(sisailmankosteus), MAX(ilmanpaine),
                            AVG(ROUNDtuulennopeus1), AVG(tuulennopeus2), AVG(tuulensuunta1), AVG(tuulensuunta2), AVG(sademaara1), AVG(sademaara2), AVG(ulkolampotila1), AVG(ulkolampotila2), AVG(ulkoilmankosteus), AVG(sisailmankosteus), AVG(ilmanpaine)
                            FROM sql_saa WHERE ( pvm BETWEEN '{$_REQUEST['alkupvm']}' AND '{$_REQUEST['loppupvm']}' )
                            AND
                            ( (tuulennopeus1 BETWEEN {$_REQUEST['MinTuulennopeus']} AND {$_REQUEST['MaxTuulennopeus']} ) AND (tuulennopeus2 BETWEEN {$_REQUEST['MinTuulennopeus']} AND {$_REQUEST['MaxTuulennopeus']}) )
                            AND
                            ( (ulkolampotila1 BETWEEN {$_REQUEST['MinLampotila']} AND {$_REQUEST['MaxLampotila']}) AND (ulkolampotila2 BETWEEN {$_REQUEST['MinLampotila']} AND {$_REQUEST['MaxLampotila']}) );";

        tarkistaYhteys($conn, $tilastoKysely);
        $tilastoKyselynTulokset = mysqli_query($conn, $tilastoKysely);
    } else if (MinMaxLampoAsetettu() && PaivamaaraAsetettu()) {
        $tilastoKysely = "SELECT MIN(tuulennopeus1), MIN(tuulennopeus2), MIN(tuulensuunta1), MIN(tuulensuunta2), MIN(sademaara1), MIN(sademaara2), MIN(ulkolampotila1), MIN(ulkolampotila2), MIN(ulkoilmankosteus), MIN(sisailmankosteus), MIN(ilmanpaine),
                             MAX(tuulennopeus1), MAX(tuulennopeus2), MAX(tuulensuunta1), MAX(tuulensuunta2), MAX(sademaara1), MAX(sademaara2), MAX(ulkolampotila1), MAX(ulkolampotila2), MAX(ulkoilmankosteus), MAX(sisailmankosteus), MAX(ilmanpaine),
                             AVG(tuulennopeus1), AVG(tuulennopeus2), AVG(tuulensuunta1), AVG(tuulensuunta2), AVG(sademaara1), AVG(sademaara2), AVG(ulkolampotila1), AVG(ulkolampotila2), AVG(ulkoilmankosteus), AVG(sisailmankosteus), AVG(ilmanpaine)
                             FROM sql_saa WHERE 
                            ( pvm BETWEEN '{$_REQUEST['alkupvm']}' AND '{$_REQUEST['loppupvm']}' )
                            AND
                            ( (ulkolampotila1 BETWEEN {$_REQUEST['MinLampotila']} AND {$_REQUEST['MaxLampotila']}) AND (ulkolampotila2 BETWEEN {$_REQUEST['MinLampotila']} AND {$_REQUEST['MaxLampotila']}) );";
        tarkistaYhteys($conn, $tilastoKysely);
        $tilastoKyselynTulokset = mysqli_query($conn, $tilastoKysely);
    } else if (MinMaxTuuliAsetettu() && PaivamaaraAsetettu()) {
        $tilastoKysely = "SELECT MIN(tuulennopeus1), MIN(tuulennopeus2), MIN(tuulensuunta1), MIN(tuulensuunta2), MIN(sademaara1), MIN(sademaara2), MIN(ulkolampotila1), MIN(ulkolampotila2), MIN(ulkoilmankosteus), MIN(sisailmankosteus), MIN(ilmanpaine),
                             MAX(tuulennopeus1), MAX(tuulennopeus2), MAX(tuulensuunta1), MAX(tuulensuunta2), MAX(sademaara1), MAX(sademaara2), MAX(ulkolampotila1), MAX(ulkolampotila2), MAX(ulkoilmankosteus), MAX(sisailmankosteus), MAX(ilmanpaine),
                             AVG(tuulennopeus1), AVG(tuulennopeus2), AVG(tuulensuunta1), AVG(tuulensuunta2), AVG(sademaara1), AVG(sademaara2), AVG(ulkolampotila1), AVG(ulkolampotila2), AVG(ulkoilmankosteus), AVG(sisailmankosteus), AVG(ilmanpaine)
                             FROM sql_saa WHERE 
                            ( pvm BETWEEN '{$_REQUEST['alkupvm']}' AND '{$_REQUEST['loppupvm']}' )
                            AND
                            ( (tuulennopeus1 BETWEEN {$_REQUEST['MinTuulennopeus']} AND {$_REQUEST['MaxTuulennopeus']} ) AND (tuulennopeus2 BETWEEN {$_REQUEST['MinTuulennopeus']} AND {$_REQUEST['MaxTuulennopeus']}) )";
        tarkistaYhteys($conn, $tilastoKysely);
        $tilastoKyselynTulokset = mysqli_query($conn, $tilastoKysely);
    } else if (MinMaxLampoAsetettu() && MinMaxTuuliAsetettu()) {
        $tilastoKysely = "SELECT MIN(tuulennopeus1), MIN(tuulennopeus2), MIN(tuulensuunta1), MIN(tuulensuunta2), MIN(sademaara1), MIN(sademaara2), MIN(ulkolampotila1), MIN(ulkolampotila2), MIN(ulkoilmankosteus), MIN(sisailmankosteus), MIN(ilmanpaine),
                             MAX(tuulennopeus1), MAX(tuulennopeus2), MAX(tuulensuunta1), MAX(tuulensuunta2), MAX(sademaara1), MAX(sademaara2), MAX(ulkolampotila1), MAX(ulkolampotila2), MAX(ulkoilmankosteus), MAX(sisailmankosteus), MAX(ilmanpaine),
                             AVG(tuulennopeus1), AVG(tuulennopeus2), AVG(tuulensuunta1), AVG(tuulensuunta2), AVG(sademaara1), AVG(sademaara2), AVG(ulkolampotila1), AVG(ulkolampotila2), AVG(ulkoilmankosteus), AVG(sisailmankosteus), AVG(ilmanpaine)
                             FROM sql_saa WHERE
                            ( (tuulennopeus1 BETWEEN {$_REQUEST['MinTuulennopeus']} AND {$_REQUEST['MaxTuulennopeus']} ) AND (tuulennopeus2 BETWEEN {$_REQUEST['MinTuulennopeus']} AND {$_REQUEST['MaxTuulennopeus']}) )
                             AND
                            ( (ulkolampotila1 BETWEEN {$_REQUEST['MinLampotila']} AND {$_REQUEST['MaxLampotila']}) AND (ulkolampotila2 BETWEEN {$_REQUEST['MinLampotila']} AND {$_REQUEST['MaxLampotila']}) );";
        tarkistaYhteys($conn, $tilastoKysely);
        $tilastoKyselynTulokset = mysqli_query($conn, $tilastoKysely);
    } else if (MinMaxLampoAsetettu()) {
        $tilastoKysely = "SELECT MIN(tuulennopeus1), MIN(tuulennopeus2), MIN(tuulensuunta1), MIN(tuulensuunta2), MIN(sademaara1), MIN(sademaara2), MIN(ulkolampotila1), MIN(ulkolampotila2), MIN(ulkoilmankosteus), MIN(sisailmankosteus), MIN(ilmanpaine),
                             MAX(tuulennopeus1), MAX(tuulennopeus2), MAX(tuulensuunta1), MAX(tuulensuunta2), MAX(sademaara1), MAX(sademaara2), MAX(ulkolampotila1), MAX(ulkolampotila2), MAX(ulkoilmankosteus), MAX(sisailmankosteus), MAX(ilmanpaine),
                             AVG(tuulennopeus1), AVG(tuulennopeus2), AVG(tuulensuunta1), AVG(tuulensuunta2), AVG(sademaara1), AVG(sademaara2), AVG(ulkolampotila1), AVG(ulkolampotila2), AVG(ulkoilmankosteus), AVG(sisailmankosteus), AVG(ilmanpaine)
                             FROM sql_saa WHERE 
                            (ulkolampotila1 BETWEEN {$_REQUEST['MinLampotila']} AND {$_REQUEST['MaxLampotila']}) AND (ulkolampotila2 BETWEEN {$_REQUEST['MinLampotila']} AND {$_REQUEST['MaxLampotila']});";
        tarkistaYhteys($conn, $tilastoKysely);
        $tilastoKyselynTulokset = mysqli_query($conn, $tilastoKysely);
    } else if (MinMaxTuuliAsetettu()) {
        $tilastoKysely = "SELECT MIN(tuulennopeus1), MIN(tuulennopeus2), MIN(tuulensuunta1), MIN(tuulensuunta2), MIN(sademaara1), MIN(sademaara2), MIN(ulkolampotila1), MIN(ulkolampotila2), MIN(ulkoilmankosteus), MIN(sisailmankosteus), MIN(ilmanpaine),
                             MAX(tuulennopeus1), MAX(tuulennopeus2), MAX(tuulensuunta1), MAX(tuulensuunta2), MAX(sademaara1), MAX(sademaara2), MAX(ulkolampotila1), MAX(ulkolampotila2), MAX(ulkoilmankosteus), MAX(sisailmankosteus), MAX(ilmanpaine),
                             AVG(tuulennopeus1), AVG(tuulennopeus2), AVG(tuulensuunta1), AVG(tuulensuunta2), AVG(sademaara1), AVG(sademaara2), AVG(ulkolampotila1), AVG(ulkolampotila2), AVG(ulkoilmankosteus), AVG(sisailmankosteus), AVG(ilmanpaine)
                             FROM sql_saa WHERE 
                            (tuulennopeus1 BETWEEN {$_REQUEST['MinTuulennopeus']} AND {$_REQUEST['MaxTuulennopeus']} ) AND (tuulennopeus2 BETWEEN {$_REQUEST['MinTuulennopeus']} AND {$_REQUEST['MaxTuulennopeus']} )";
        tarkistaYhteys($conn, $tilastoKysely);
        $tilastoKyselynTulokset = mysqli_query($conn, $tilastoKysely);
    } else if (PaivamaaraAsetettu()) {             //###################################################################
        $tilastoKysely = "SELECT MIN(tuulennopeus1), MIN(tuulennopeus2), MIN(tuulensuunta1), MIN(tuulensuunta2), MIN(sademaara1), MIN(sademaara2), MIN(ulkolampotila1), MIN(ulkolampotila2), MIN(ulkoilmankosteus), MIN(sisailmankosteus), MIN(ilmanpaine),
                             MAX(tuulennopeus1), MAX(tuulennopeus2), MAX(tuulensuunta1), MAX(tuulensuunta2), MAX(sademaara1), MAX(sademaara2), MAX(ulkolampotila1), MAX(ulkolampotila2), MAX(ulkoilmankosteus), MAX(sisailmankosteus), MAX(ilmanpaine),
                             AVG(tuulennopeus1), AVG(tuulennopeus2), AVG(tuulensuunta1), AVG(tuulensuunta2), AVG(sademaara1), AVG(sademaara2), AVG(ulkolampotila1), AVG(ulkolampotila2), AVG(ulkoilmankosteus), AVG(sisailmankosteus), AVG(ilmanpaine)
                             FROM sql_saa WHERE pvm BETWEEN '{$_POST['alkupvm']}' AND '{$_POST['loppupvm']}';";
        tarkistaYhteys($conn, $tilastoKysely);
        $tilastoKyselynTulokset = mysqli_query($conn, $tilastoKysely);
    } else {
        $tilastoKysely = "SELECT MIN(tuulennopeus1), MIN(tuulennopeus2), MIN(tuulensuunta1), MIN(tuulensuunta2), MIN(sademaara1), MIN(sademaara2), MIN(ulkolampotila1), MIN(ulkolampotila2), MIN(ulkoilmankosteus), MIN(sisailmankosteus), MIN(ilmanpaine),
                             MAX(tuulennopeus1), MAX(tuulennopeus2), MAX(tuulensuunta1), MAX(tuulensuunta2), MAX(sademaara1), MAX(sademaara2), MAX(ulkolampotila1), MAX(ulkolampotila2), MAX(ulkoilmankosteus), MAX(sisailmankosteus), MAX(ilmanpaine),
                             AVG(tuulennopeus1), AVG(tuulennopeus2), AVG(tuulensuunta1), AVG(tuulensuunta2), AVG(sademaara1), AVG(sademaara2), AVG(ulkolampotila1), AVG(ulkolampotila2), AVG(ulkoilmankosteus), AVG(sisailmankosteus), AVG(ilmanpaine)
                             FROM sql_saa;";
        tarkistaYhteys($conn, $tilastoKysely);
        $tilastoKyselynTulokset = mysqli_query($conn, $tilastoKysely);
    }
?>