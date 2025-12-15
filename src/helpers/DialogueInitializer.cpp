#include "helpers/DialogueInitializer.h"
#include "model/dialogue/Dialogue.h"
#include <iostream>
#include "model/Player.h"

void DialogueInitializer::initializeDialogues(DialogueManager& manager) {
    DialogueNode ending;
    ending
        .id("ending")
        ->speaker("Концовка")
        ->text("")
        ->choice({ "Начать заново", "end", "", "restart" } )
        ->choice({"Выйти из игры", "end", "", "quit" } );

    DialogueNode end;
    end
        .id("end")
        ->speaker("")
        ->text("Вы уходите.");
    DialogueNode no_resources;
    no_resources
        .id("no_resources")
        ->speaker("Внимание")
        ->text("Вам не хватает необходимых ресурсов.")
        ->choice({"Назад", "start"});

// ========================= ПРЕДЫСТОРИЯ / ВСТУПЛЕНИЕ =========================
    Dialogue prologue("prologue");

    DialogueNode prologue1;
    prologue1
        .id("start")
        ->speaker("Система")
        ->text("Вы детектив. Ваша задача - расследовать убийство поп-звезды, по возможности не привлекая лишнего внимания и не светя полицейским жетоном (не более 3 применений).")
        ->choice({"Далее", "page2"});

    DialogueNode prologue2;
    prologue2
        .id("page2")
        ->speaker("Система")
        ->text("У Вас есть 2 денежные купюры, 3 единицы здоровья и 2 шанса на флирт. Вы должны расследовать убийство в отеле, поочередно расспрашивая всех подозреваемых, с каждым из них вы можете встретиться только 1 раз.")
        ->choice({"Далее", "page3"});

    DialogueNode prologue3;
    prologue3
        .id("page3")
        ->speaker("Система")
        ->text("Одного подозреваемого Вам собеседник назовет добровольно. Чтобы получить информацию о другом подозреваемом, Вам нужно правильно воздействовать на собеседника.")
        ->choice({"Далее", "page4"});

    DialogueNode prologue4;
    prologue4
        .id("page4")
        ->speaker("Система")
        ->text("У Вас будет только 1 шанс на воздействие, поэтому хорошенько подумайте, прежде чем выбрать способ: жетон, деньги, силу или флирт.")
        ->choice({"Далее", "page5"});

    DialogueNode prologue5;
    prologue5
        .id("page5")
        ->speaker("Система")
        ->text("Неудачный выбор воздействия может иметь для Вас негативные последствия.")
        ->choice({"Далее", "page6"});

    DialogueNode prologue6;
    prologue6
        .id("page6")
        ->speaker("Система")
        ->text("Опросив всех подозреваемых Вы должны будете сделать выбор, кому предъявить обвинение. Неправильно сделанный выбор погубит Вашу карьеру, правильный приведет к Вашему продвижению по служебной лестнице.")
        ->choice({"Далее", "crime"});

    DialogueNode crime1;
    crime1
        .id("crime")
        ->speaker("Информация")
        ->text("Поп-идол убит ночью ударом тупого продолговатого предмета по голове.")
        ->choice({"Далее", "crime2"});

    DialogueNode crime2;
    crime2
        .id("crime2")
        ->speaker("Информация")
        ->text("Ваши подозреваемые:")
        ->choice({"Далее", "crime3"});

    DialogueNode crime3;
    crime3
        .id("crime3")
        ->speaker("Информация")
        ->text("Х - хозяин отеля, он же бармен в баре при отеле")
        ->choice({"Далее", "crime4"});

    DialogueNode crime4;
    crime4
        .id("crime4")
        ->speaker("Информация")
        ->text("О - охранник")
        ->choice({"Далее", "crime5"});

    DialogueNode crime5;
    crime5
        .id("crime5")
        ->speaker("Информация")
        ->text("S - стриптизёрша в баре, девушка лёгкого поведения")
        ->choice({"Далее", "crime6"});

    DialogueNode crime6;
    crime6
        .id("crime6")
        ->speaker("Информация")
        ->text("D - слепой дед с собакой-поводырём, скандальный, жил напротив убитого")
        ->choice({"Далее", "crime7"});

    DialogueNode crime7;
    crime7
        .id("crime7")
        ->speaker("Информация")
        ->text("F - постоялец средних лет, тихий, в очках, сосед убитого слева")
        ->choice({"Далее", "crime8"});

    DialogueNode crime8;
    crime8
        .id("crime8")
        ->speaker("Информация")
        ->text("B - бабулька с костылем, соседка убитого справа")
        ->choice({"Далее", "crime9"});

    DialogueNode crime9;
    crime9
        .id("crime9")
        ->speaker("Информация")
        ->text("Беседу с каждым из них Вы уже начали с вопросов 'Что Вы делали в момент убийства?' и 'Кого Вы подозреваете?'")
        ->choice({"Далее", "crime10"});

    DialogueNode crime10;
    crime10
        .id("crime10")
        ->speaker("Готовы???")
        ->text("Когда будете готовы - вернитесь на место преступления (номер поп-идола на втором этаже отеля)")
        ->choice({"Начать расследование", "end"});

    prologue.addNode(prologue1);
    prologue.addNode(prologue2);
    prologue.addNode(prologue3);
    prologue.addNode(prologue4);
    prologue.addNode(prologue5);
    prologue.addNode(prologue6);
    prologue.addNode(end);

    prologue.addNode(crime1);
    prologue.addNode(crime2);
    prologue.addNode(crime3);
    prologue.addNode(crime4);
    prologue.addNode(crime5);
    prologue.addNode(crime6);
    prologue.addNode(crime7);
    prologue.addNode(crime8);
    prologue.addNode(crime9);
    prologue.addNode(crime10);

    // ========================= ХОЗЯИН ОТЕЛЯ (Х) =========================
    Dialogue hotelOwner("hotel_owner");

    DialogueNode start;
    start
        .id("start")
        ->speaker("Хозяин отеля")
        ->text("Я всю ночь простоял за барной стойкой, охранник может подтвердить. Убитый был в очень плохих отношениях со своей пожилой соседкой справа, она всё время жаловалась, что он громко распевается в номере и мешает ей. Неоднократно вызывали охрану для погашения конфликта.")
        ->choice({"Показать жетон", "badge", "has_badge",   "remove_badge"})
        ->choice({"Дать деньги",    "money", "has_money_2", "remove_money_2"})
        ->choice({"Флиртовать",     "flirt", "has_flirt",   "remove_flirt_plus_hp"})
        ->choice({"Применить силу", "force", "has_health",  "take_damage"});

    DialogueNode badge;
    badge
        .id("badge")
        ->speaker("Хозяин отеля")
        ->text("О, так Вы не просто полицейский, Вы из ФБР! Но для меня без разницы, где Вы работаете. В конце концов, именно я позвонил в 911 и вызвал Вас. Вам следовало выбрать другой метод воздействия. До свидания!")
        ->choice({"Уйти", "end"});

    DialogueNode money;
    money
        .id("money")
        ->speaker("Хозяин отеля")
        ->text("Моя разговорчивость, боюсь, обошлась Вам дороже, чем Вы планировали. *Ухмыляется, поигрывая тяжёлым, металлическим шейкером* Впрочем, вот Вам второй подозрительный с моей точки зрения человек: слепец с его мерзкой собакой-поводырём. Собака начинала выть, когда поп-идол пел, а у певца была аллергия на собачью шерсть, из-за чего старик со звездой часто ругались и угрожали друг другу. Приходилось даже вызывать охрану.")
        ->choice({"Уйти", "end"});

    DialogueNode flirt;
    flirt
        .id("flirt")
        ->speaker("Хозяин отеля")
        ->text("Боюсь, Вы не в моем вкусе, детектив. Впрочем, любезность за любезность: позвольте угостить Вас обедом за счёт заведения. Это придаст Вам сил. Вот Вам второй подозрительный с моей точки зрения человек: слепец с его мерзкой собакой-поводырём. Собака начинала выть, когда поп-идол пел, а у певца была аллергия на собачью шерсть, из-за чего старик со звездой часто ругались и угрожали друг другу. Приходилось даже вызывать охрану.")
        ->choice({"Уйти", "end"});

    DialogueNode force;
    force
        .id("force")
        ->speaker("Хозяин отеля")
        ->text("Вытирая кровь с губ... Вот Вам второй подозрительный с моей точки зрения человек: слепец с его мерзкой собакой-поводырём. Собака начинала выть, когда поп-идол пел, а у певца была аллергия на собачью шерсть, из-за чего старик со звездой часто ругались и угрожали друг другу. Приходилось даже вызывать охрану.")
        ->choice({"Уйти", "end"});

    hotelOwner.addNode(start);
    hotelOwner.addNode(badge);
    hotelOwner.addNode(money);
    hotelOwner.addNode(flirt);
    hotelOwner.addNode(force);
    hotelOwner.addNode(no_resources);
    hotelOwner.addNode(end);

    // ========================= ОХРАННИК (О) =========================
    Dialogue guard("guard");

    DialogueNode o_start;
    o_start
        .id("start")
        ->speaker("Охранник")
        ->text("Я всю смену провёл в баре, присматривая за посетителями, хозяин и стриптизёрша могут подтвердить. А если хотите знать, кого я подозреваю в первую очередь, так это старика с собакой. Меня частенько вызывали успокаивать этих двух постояльцев, они кричали на всю гостиницу.")
        ->choice({"Показать жетон", "badge", "has_badge", "remove_badge"})
        ->choice({"Дать деньги", "money", "has_money", "remove_money"})
        ->choice({"Флиртовать", "ending", "has_flirt", "remove_flirt"})
        ->choice({"Применить силу", "force", "has_health_2", "take_damage_2"}); // -2 силы

    DialogueNode o_badge;
    o_badge
        .id("badge")
        ->speaker("Охранник")
        ->text("О, ФБР! Помогу, чем смогу! Мне очень подозрительным кажется этот тихий очкарик, что живёт слева от убитого. Он заселился в тот же день, что и поп-идол, и всё время ходил за ним по пятам, словно сталкер какой-то. И глаза у него такие злые делались, если звезда кому-то улыбался...")
        ->choice({"Уйти", "end"});

    DialogueNode o_money;
    o_money
        .id("money")
        ->speaker("Охранник")
        ->text("Я не продаюсь, понял? Засунь себе эти деньги знаешь куда?")
        ->choice({"Уйти", "end"});

    ending.text("Ты на что намекаешь, грязный извращенец?! На, получай! *Вы получили телесные повреждения, не совместимые с жизнью*");

    DialogueNode o_force;
    o_force
        .id("force")
        ->speaker("Охранник")
        ->text("*Вы обмениваетесь несколькими ударами. Охранник явно сильнее Вас. Он заламывает вам руку. Впрочем, подумав пару секунд соглашается-таки ответить на Ваш вопрос о втором подозреваемом* Мне очень подозрительным кажется этот тихий очкарик, что живёт слева от убитого. Он заселился в тот же день, что и поп-идол, и всё время ходил за ним по пятам, словно сталкер какой-то. И глаза у него такие злые делались, если звезда кому-то улыбался...")
        ->choice({"Уйти", "end"});

    guard.addNode(o_start);
    guard.addNode(o_badge);
    guard.addNode(o_money);
    guard.addNode(ending);
    guard.addNode(o_force);
    guard.addNode(no_resources);
    guard.addNode(end);

    // ========================= СТРИПТИЗЁРША (С) =========================
    Dialogue stripper("stripper");

    DialogueNode s_start;
    s_start
        .id("start")
        ->speaker("Стриптизёрша")
        ->text("Я всю ночь протанцевала на пилоне, ни с кем в номера не ходила, ни один клиент не подвернулся. Охранник может подтвердить, что я никуда не отлучалась. А убийца, я думаю, очкарик этот. Была я у него в номере, так там в углу комнаты фотографии поп-идола висят. А если кто рядом на фото со звездой, так непременно глаза у того выколоты или замулёваны, стрём такой!")
        ->choice({"Показать жетон", "badge", "has_badge", "remove_badge"})
        ->choice({"Дать деньги", "money", "has_money", "remove_money"})
        ->choice({"Флиртовать", "flirt", "has_flirt", "remove_flirt"})
        ->choice({"Применить силу", "force", "has_health", "take_damage"});

    DialogueNode s_badge;
    s_badge
        .id("badge")
        ->speaker("Стриптизёрша")
        ->text("Да ты спрячь свою железяку, ковбой! Не напугаешь меня ею, пуганая я. Неправильный подход у тебя к девушкам, ничего тебе не скажу!")
        ->choice({"Уйти", "end"});

    DialogueNode s_money;
    s_money
        .id("money")
        ->speaker("Стриптизёрша")
        ->text("Спасибо, милый, позолотил ручку, слушай тогда. Уж очень хозяин гостиницы зол на поп-идола этого был! Да оно и понятно: то орёт-распевается, то с соседями ругается, разнимать приходится. А спьяну в баре не только ко мне, даже к хозяину гостиницы целоваться лез, кому это понравится?")
        ->choice({"Уйти", "end"});

    DialogueNode s_flirt;
    s_flirt
        .id("flirt")
        ->speaker("Стриптизёрша")
        ->text("Руки убери! Мне таких бойких на работе хватает, достали уже! И ты достал, отвали!")
        ->choice({"Уйти", "end"});

    DialogueNode s_force;
    s_force
        .id("force")
        ->speaker("Стриптизёрша")
        ->text("По лицу зачем бьешь, начальник? Ладно, ладно, скажу... Уж очень хозяин гостиницы зол на поп-идола этого был! Да оно и понятно: то орёт-распевается, то с соседями ругается, разнимать приходится. А спьяну в баре не только ко мне, даже к хозяину гостиницы целоваться лез, кому это понравится?")
        ->choice({"Уйти", "end"});

    stripper.addNode(s_start);
    stripper.addNode(s_badge);
    stripper.addNode(s_money);
    stripper.addNode(s_flirt);
    stripper.addNode(s_force);
    stripper.addNode(no_resources);
    stripper.addNode(end);

    // ========================= СЛЕПОЙ ДЕД (Д) =========================
    Dialogue blind("blind_man");

    DialogueNode d_start;
    d_start
        .id("start")
        ->speaker("Слепой дед")
        ->text("Да вы там с ума в своей полиции посходили?! Слепого подозреваете?! В номере я у себя был! А на Вашем месте бы к хозяину гостиницы присмотрелся: я не раз слышал, как он охраннику говорил, что такого постояльца убить мало...")
        ->choice({"Показать жетон", "badge", "has_badge", "remove_badge"})
        ->choice({"Дать деньги", "money", "has_money", "remove_money"})
        ->choice({"Флиртовать", "flirt", "has_flirt_hp", "remove_flirt_double"}) // -1 флирт и -1 сила
        ->choice({"Применить силу", "force", "has_health_2", "take_damage_2"}); // -2 силы

    DialogueNode d_badge;
    d_badge
        .id("badge")
        ->speaker("Слепой дед")
        ->text("ФБР? Так уж и быть, помогу чем смогу. Советую Вам присмотреться к старухе с нашего этажа. Она только выглядит слабой, а сама молодым фору даст! Всё пыталась артиста этого клюкой своей ударить, да и по этажу быстрее молодых бегает.")
        ->choice({"Уйти", "end"});

    DialogueNode d_money;
    d_money
        .id("money")
        ->speaker("Слепой дед")
        ->text("Не смеши меня, мальчишка. У меня достаточно денег, да и тратить мне их особо не на что. Уходи, пока я собаку на тебя не спустил!")
        ->choice({"Уйти", "end"});

    DialogueNode d_flirt;
    d_flirt
        .id("flirt")
        ->speaker("Слепой дед")
        ->text("Ах ты мерзкий извращенец! Куси его, Трезор!")
        ->choice({"Уйти", "end"});

    DialogueNode d_force;
    d_force
        .id("force")
        ->speaker("Слепой дед")
        ->text("*В ответ на попытку ударить старика Вы были покусаны собакой*")
        ->choice({"Уйти", "end"});

    blind.addNode(d_start);
    blind.addNode(d_badge);
    blind.addNode(d_money);
    blind.addNode(d_flirt);
    blind.addNode(d_force);
    blind.addNode(end);

    // ========================= ОЧКАРИК (П) =========================
    Dialogue fan("fan");

    DialogueNode p_start;
    p_start
        .id("start")
        ->speaker("Постоялец")
        ->text("Я человек одинокий, тихий. У меня режим. Конечно же, я, как обычно, в это время уже спал. Да и как я мог бы покуситься на жизнь моего кумира! Я ведь так люблю его. У меня даже есть микрофон с его автографом, посмотрите! А вот кто действительно моего кумира недолюбливал, так это охранник отеля: всё время грозился поколотить его и вышвырнуть из отеля из-за его пения и ссор с другими постояльцами. Глупые люди не понимают тонкую трепетную натуру моего кумира!")
        ->choice({"Показать жетон", "badge", "has_badge", "remove_badge"})
        ->choice({"Дать деньги", "money", "has_money", "remove_money"})
        ->choice({"Флиртовать", "flirt", "has_flirt", "remove_flirt"})
        ->choice({"Применить силу", "force", "has_health", "take_damage"});

    DialogueNode p_badge;
    p_badge
        .id("badge")
        ->speaker("Постоялец")
        ->text("Я с радостью расскажу вам всё, что знаю, офицер! Стриптизёрша из бара! Я позавчера и в ночь убийства видел, как она поутру выходила из номера моего кумира. Она единственная, кого он пускал в свой номер.")
        ->choice({"Уйти", "end"});

    DialogueNode p_money;
    p_money
        .id("money")
        ->speaker("Постоялец")
        ->text("*Кивает, прячет купюру в карман* Стриптизёрша из бара! Я позавчера и в ночь убийства видел, как она поутру выходила из номера моего кумира. Она единственная, кого он пускал в свой номер.")
        ->choice({"Уйти", "end"});

    DialogueNode p_flirt;
    p_flirt
        .id("flirt")
        ->speaker("Постоялец")
        ->text("В моем сердце только 1 человек, мой кумир! Но тем не менее, ради его памяти, я помогу Вам всем, чем смогу! Стриптизёрша из бара! Я позавчера и в ночь убийства видел, как она поутру выходила из номера моего кумира. Она единственная, кого он пускал в свой номер.")
        ->choice({"Уйти", "end"});

    DialogueNode p_force;
    p_force
        .id("force")
        ->speaker("Постоялец")
        ->text("Вам не обязательно было бить меня, я и так готов всемерно сотрудничать в поисках убийцы моего кумира. Стриптизёрша из бара! Я позавчера и в ночь убийства видел, как она поутру выходила из номера моего кумира. Она единственная, кого он пускал в свой номер.")
        ->choice({"Уйти", "end"});

    fan.addNode(p_start);
    fan.addNode(p_badge);
    fan.addNode(p_money);
    fan.addNode(p_flirt);
    fan.addNode(p_force);
    fan.addNode(no_resources);
    fan.addNode(end);

    // ========================= БАБУЛЬКА (Б) =========================
    Dialogue granny("granny");

    DialogueNode b_start;
    b_start
        .id("start")
        ->speaker("Бабушка")
        ->text("Да уж конечно я была в своей комнате! Я приличная женщина, а не какая-нибудь там особа с низкой социальной ответственностью! В отличие от стриптизёрши, которая вешалась на убитого и занималась с ним в номере неизвестно чем!")
        ->choice({"Показать жетон", "badge", "has_badge", "remove_badge"})
        ->choice({"Дать деньги", "money", "has_money", "remove_money"})
        ->choice({"Флиртовать", "flirt", "has_flirt", "remove_flirt_plus_money"}) // -1 флирт, +1 деньги
        ->choice({"Применить силу", "ending", "has_health", ""}); // КОНЦОВКА

    DialogueNode b_badge;
    b_badge
        .id("badge")
        ->speaker("Бабушка")
        ->text("Да ты в лицо мне своей железкой на тыкай! Я юристом 30 лет работала и свои права знаю!")
        ->choice({"Уйти", "end"});

    DialogueNode b_money;
    b_money
        .id("money")
        ->speaker("Бабушка")
        ->text("Убери свои купюры! Я честная женщина, а не какая-то там стриптизёрша, чтобы деньги у мужика брать!")
        ->choice({"Уйти", "end"});

    DialogueNode b_flirt;
    b_flirt
        .id("flirt")
        ->speaker("Бабушка")
        ->text("Ох, уважил бабушку, милок! Порадовал на старость лет! Вот денюжка тебе за это от меня, возьми! А подозреваю я охранника. Ходит злой, дубинкой своей машет, почти каждый день приходил с поп-идолом этим ругаться! Мог и убить невзначай, сил-то у него немеряно!")
        ->choice({"Уйти", "end"});

    ending.text("*Вы не рассчитали удар, старушка упала и умерла. Вы арестованы и будете осуждены за убийство*");

    granny.addNode(b_start);
    granny.addNode(b_badge);
    granny.addNode(b_money);
    granny.addNode(b_flirt);
    granny.addNode(ending);
    granny.addNode(no_resources);
    granny.addNode(end);

    // ========================= ФИНАЛЬНОЕ РЕШЕНИЕ ====================
    Dialogue final("final_choice");
    DialogueNode final1;
    final1
        .id("start")
        ->speaker("Финальное решение")
        ->text("Настало время финального решения, думайте чательно, детектив...")
        ->choice({"Роберт: Хозяин отеля", "false"})
        ->choice({"Стефанни: Стриптизёрша", "false"})
        ->choice({"Виктор: Охранник", "false"})
        ->choice({"Френк: Постоялец", "true"})
        ->choice({"Димон: Слепой дед", "false"})
        ->choice({"Елизавета: Бабулька", "false"})
        ->choice({"Я не готов", "end" })
    ;
    DialogueNode f;
    f
        .id("false")
        ->speaker("Вы ошиблись")
        ->text("К большому сожелению вы сделали неверный вывод, когда это вскрылось общественность обозлилась на Вас, в итоге вы потеряли работу, а люди, узнающие вас на улице, смотрят на вас с презрением")
        ->choice({ "Попробовать снова", "end", "", "restart" } )
        ->choice({"Уйти с позором", "end", "", "quit" } );
    DialogueNode t;
    t
        .id("true")
        ->speaker("ПОБЕДА!!!")
        ->text("К великому счастью вы оказались правы, все многочисленные фанаты поп-идола благодарный вам за восторжествовавшую справедливость, за такой успех вы получили значительной повышение в должности, а люди, узнающие вас на улице, иногда подходят фоткаться")
        ->choice({"Поздравляем Вас победой (Команда: Супернатуралы)", "end", "", "quit" } );

    final.addNode(final1);
    final.addNode(f);
    final.addNode(t);
    final.addNode(end);

    // ========================= УЖЕ ГОВОРИЛИ =========================
    Dialogue alreadyTalked("already_talked");
    DialogueNode at_start;
    at_start
        .id("start")
        ->speaker("")
        ->text("Вы уже распросили этого персонажа")
        ->choice({"Уйти", "end"});
    alreadyTalked.addNode(at_start);
    alreadyTalked.addNode(end);

    // Регистрация всех диалогов
    manager.registerDialogue(std::move(prologue));
    manager.registerDialogue(std::move(hotelOwner));
    manager.registerDialogue(std::move(guard));
    manager.registerDialogue(std::move(stripper));
    manager.registerDialogue(std::move(blind));
    manager.registerDialogue(std::move(fan));
    manager.registerDialogue(std::move(granny));
    manager.registerDialogue(std::move(alreadyTalked));
    manager.registerDialogue(std::move(final));
}