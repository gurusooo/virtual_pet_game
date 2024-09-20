  function setName() {
      let name = document.getElementById('cat-name').value;
      if (name) {
          Module._set_cat_name(name);
      }
  }

  function feedCat() {
      Module._feed_cat();
  }

  function playCat() {
      Module._play_cat();
  }

  function groomCat() {
      Module._groom_cat();
  }

  function leaveCat() {
      Module._leave_cat();
  }
