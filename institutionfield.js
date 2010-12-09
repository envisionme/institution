$(document).ready(function() {
  
  var numboxes = $("input[type=checkbox]").length;

  for(var k=0; k < numboxes; k++) {
    if ($("#edit-field-app-qualification-"+k+"-currentstudent").is(':checked')) {
      $("#edit-field-app-qualification-"+k+"-year-year").attr("disabled", "disabled");
    }
    else {
      $("#edit-field-app-qualification-"+k+"-year-year").removeAttr('disabled');
    }
  }
  
  $("input[type=checkbox]").click(function() {
    var numboxes = $("input[type=checkbox]").length;
    for(var k=0; k < numboxes; k++) {
      //~ alert('checkbox changed');
      if ($("#edit-field-app-qualification-"+k+"-currentstudent").is(':checked')) {
        $("#edit-field-app-qualification-"+k+"-year-year").attr("disabled", "disabled");
        //~ alert('checked');
      }
      else {
        $("#edit-field-app-qualification-"+k+"-year-year").removeAttr('disabled');
        //~ alert('unchecked');
      }
    }
  });

});
