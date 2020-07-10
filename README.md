Update:

1) Program was refactored to model/view. But we still must use update function from view after each
update from model, because view must add buttons for add/remove favorite and update alphabetical jump button
block.
2) Add repaint grid view on resize event to fix problem: " GridView means that contact tile size is fixed but 
when you change window size it tries to fill free horizontal space (maybe with Model you may use TableView, 
check QML GridView for reference)".
3) Because all data handling was moved to viewModel class we can use another view with this model and do not need
rewrite data handling algorithms. All what we need it write ui logic to interaction with viewModel.
4) On my linux system (Manjaro linux arch based distribution) with g++ compiler version: 10.1.0 and 
qt version: 5.15.0-0 project compiles fine and I do not know why you have got problem with this.
5) DB was deleted and set/unset favorite state now directly in ContactListProvider.

These were made:

1) Absolute minimal valuable product would show contact list with names at the center of each cell.
2) Circle contact list pictures at the left side.
3) Call function: by tap you call ContactListProvider::call(id) and indicate somehow active call.
    Notice: if you do not cancel call for 10 seconds ContactListProvider::call(id) will cancel call by itself
    to show program ability to process situations when your interlocutor cancel this call. For canceling call
    by yourself to ContactListProvider was added function endCall().
4) Grid view switcher for our contact viewer (here contact pictures “must have”).
5) Favorites: possibility to add to favorites (use star/plus button) and show only favorites.
    Notice: remove from favorite is exist too.
6) Local filter: text field by using which we may filter out contacts (great if “on the fly”).
    Notice: on the fly local filter. In "show all" mode filter show all contacts which have letter or string what
    was inputted in search field. In "show only favorites" mode filter show only suitable contacts with favorite
    "mark". If you change show mode, you do not need to input your search again. Does not depend on letters case.
7) Alphabetical jump: service provides getAvailableLetters chars and sorted contact list.

Tech-stack: Qt + QtWidgets. IDE: QtCreator on windows with MSVC2019 compiler.
