$(document).ready(function () {
    //плавное перемещение страницы к нужному блоку 
    $("a").click(function () {
        elementClick = $(this).attr("href");
        destination = $(elementClick).offset().top;
        $("body,html").animate({ scrollTop: destination }, 500);
    });
});


