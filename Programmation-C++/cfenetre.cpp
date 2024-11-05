#include "cfenetre.h"

CFenetre::CFenetre() : QWidget()
{
    m_ecgfenetre = new Csousfenetre;
    m_bouton = new QPushButton("ouvrir image", this);

    m_calculateur = new CCalcul;

    instructionlabel = new QLabel("Instructions");
    instructionlabel->setText("<h3>Instructions:</h3>"
                             "<p>Pour mesurer une longueur, faire clique droit pour créer le premier point.</p>"
                             "<p>Puis faire clique gauche pour créer le second point correspondant à la fin de la ligne.</p>"
                             "<p>Pour effacer,   appuyer sur clique droit.</p>");

    imagetuto = new QLabel();
    pixmap = QPixmap("/Users/khadidja/Desktop/imagetuto2.png");
    imagetuto->setPixmap(pixmap);

// Widget pour définir echelle

     m_groupbox = new QGroupBox("Définir échelle");

    labeltemps = new QLabel("temps échelle :");
     m_timebox = new QDoubleSpinBox();
     m_timebox->setMinimum(0);
     m_timebox->setMaximum(10000000.0);
     m_timebox->setSingleStep(0.1);

     labelunite = new QLabel("unité");
     m_unitebox = new QComboBox();
     m_unitebox->addItem("s");
     m_unitebox->addItem("ms");
     m_unitebox->addItem("us");

     m_boutonok= new QPushButton("Valider", this);
     m_boutonaide = new QPushButton("Aide", this);

     m_gridlayout = new QGridLayout(this);
     m_gridlayout->addWidget(labeltemps, 0, 0);
     m_gridlayout->addWidget(m_timebox, 0, 1);
     m_gridlayout->addWidget(labelunite, 1, 0);
     m_gridlayout->addWidget(m_unitebox, 1, 1);
     m_gridlayout->addWidget(m_boutonaide, 2,0);
     m_gridlayout->addWidget(m_boutonok, 2, 1);

     m_groupbox->setLayout(m_gridlayout);

     m_fcgroupbox = new QGroupBox("Fréquence cardiaque");
     m_label = new QLabel("Frequence cardiaque: ");
     m_fclabel= new QLabel;
     m_fcbutton= new QPushButton("Calcul de la fréquence", this);

     m_fclayout=new QGridLayout(this);
     m_fclayout->addWidget(m_fcbutton,0,0);
     m_fclayout->addWidget(m_label, 1,0);
     m_fclayout->addWidget(m_fclabel,1,1);
     m_fcgroupbox->setLayout(m_fclayout);

// DISPOSITION DES WIDGETS
    QVBoxLayout* m_menulayout = new QVBoxLayout();
    QHBoxLayout* m_ecglayout = new QHBoxLayout(this);

//Layout vertical
    m_menulayout->addWidget(m_bouton);
    m_menulayout->addWidget(instructionlabel);
    m_menulayout->addWidget(imagetuto);
    m_menulayout->addWidget(m_groupbox);
    m_menulayout->addWidget(m_fcgroupbox);
    m_menulayout->addStretch();

//LayoutHorizontal
    m_ecglayout->addLayout(m_menulayout);
    m_ecglayout->addWidget(m_ecgfenetre);

    m_groupbox->setDisabled(1);
    m_fcgroupbox->setDisabled(1);

    connect(m_bouton,SIGNAL(clicked()),m_ecgfenetre,SLOT(ouvrirImage()));
    connect(m_bouton,SIGNAL(clicked()),this,SLOT(echelledispo()));

    connect(m_boutonok, SIGNAL(clicked()), this, SLOT(setscale()));
    connect(m_boutonaide, SIGNAL(clicked()), this, SLOT(scalehelp()));

    connect(m_fcbutton, SIGNAL(clicked()), this, SLOT(affichefc()));

   /* QGroupBox {
        border-style: outset;
        border-width: 2px solid;
        border-color : gray;
        border-radius: 5px; } bon ça marche pas */
}

CFenetre::~CFenetre()
{
delete m_bouton;
delete m_fcbutton;

delete m_ecgfenetre;
delete m_calculateur;

delete m_menulayout;
delete m_ecglayout;

delete m_groupbox;
delete m_gridlayout;
delete m_boutonok;
delete m_boutonaide;
delete m_timebox;
delete m_unitebox;
delete labeltemps;
delete labelunite;

delete m_fcgroupbox;
delete m_label;
delete m_fclabel;
delete m_fclayout;

delete instructionlabel;
delete imagetuto;
}

void CFenetre::setscale(){

    // je récupère les valeurs que l'utilisateur rentre.
    QString unite = m_unitebox->currentText();
    double valeuruser= m_timebox->value();
    double distance = m_ecgfenetre->getDistPixel();

    // je m'en sers pour calculer l'équivalent pixel/temps
    double distechelle = m_calculateur->calculatescale(valeuruser, unite, m_ecgfenetre);

    m_scalefactor= distechelle; //pour stocker ma valeur finale

    qDebug() <<m_scalefactor;

    if (valeuruser == 0 && distance == 0 ) {
        QMessageBox::warning(this, "Warning", "Échelle non définie.\nPour plus d'informations, appuyer sur AIDE.");
    }
    else{
        QMessageBox msg;
         msg.setText("Échelle bien définie.");
         msg.exec();
         m_fcgroupbox->setDisabled(0);
    }
    qDebug() << "valeuruser= " << valeuruser << "dist= " << distance;
}

void CFenetre::affichefc()
{
    double distpixel2 = m_ecgfenetre->getDistPixel();
    double freq= 60*m_scalefactor/ distpixel2 ;

    m_frequence= round(freq);

    m_fclabel->setText(tr(" %1 bpm").arg(m_frequence));

    qDebug() << "echelle = " << m_scalefactor;
    qDebug()<< "freq cardiaque= " << m_frequence;
}

void CFenetre::echelledispo(){
    m_groupbox->setDisabled(0);
}

void CFenetre::scalehelp(){
    QString instructions = "Pour définir l'échelle:\n\n";
     instructions += "1. Selectionnez vos deux points sur le papier ECG pour tracer la ligne.\n\n";
     instructions += "2. Entrez l'équivalent en temps dans le champ de texte temps échelle puis valider.\n\n";
     instructions += "Notez que l'échelle n'est pas validé si : aucune ligne n'a été tracée ET aucune valeur en temps n'a été donnée.\n";

     QMessageBox::information(this, "Aide pour définir l'échelle.", instructions);
}

