my $var = `ls ./img/`;
#print($var);
my @res = split(/\n/ , $var);
my $tmp;
foreach $tmp (@res)
{
    my $my_tmp = `echo $tmp | cut -d \".\" -f 1`;
    chop($my_tmp);
    $tmp = "./img/" . $tmp;
    $my_tmp = "./img/" . $my_tmp;
#    print("convert $tmp $my_tmp".".png");
     system("convert $tmp $my_tmp".".png");
} 
