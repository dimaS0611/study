$(document).ready(function () {
    //������� ����������� �������� � ������� ����� 
    $("a").click(function () {
        elementClick = $(this).attr("href");
        destination = $(elementClick).offset().top;
        $("body,html").animate({ scrollTop: destination }, 500);
    });
});


