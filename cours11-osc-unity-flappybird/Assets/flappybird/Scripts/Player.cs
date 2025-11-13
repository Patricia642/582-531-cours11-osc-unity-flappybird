using UnityEngine;
using extOSC;//important


public class Player : MonoBehaviour
{
    public extOSC.OSCReceiver oscReceiver; //important
    //important
    public static float Proportion(float value, float inputMin, float inputMax, float outputMin, float outputMax)
{
    return Mathf.Clamp(((value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin), outputMin, outputMax);
}

private int etatEnMemoire = 1; // Le code initalise l'état initial du bouton comme relâché

//important
void TraiterOscBUTTON(OSCMessage message)
{
// Si le message n'a pas d'argument ou l'argument n'est pas un Int on l'ignore
    if (message.Values.Count == 0)
    {
        Debug.Log("No value in OSC message");
        return;
    }
        
    if (message.Values[0].Type != OSCValueType.Int)
    {
        Debug.Log("Value in message is not an Int");
        return;
    }

    // Récupérer la valeur de l’Key unit / button depuis le message OSC
    int value = message.Values[0].IntValue; 

    int nouveauEtat = value; // REMPLACER ici les ... par le code qui permet de récuérer la nouvelle donnée du flux
    if (etatEnMemoire != nouveauEtat) { // Le code compare le nouvel etat avec l'etat en mémoire
    etatEnMemoire = nouveauEtat; // Le code met à jour l'état mémorisé
    if ( nouveauEtat == 0  ) {
        // METTRE ici le code pour lorsque le bouton est appuyé
         direction = Vector3.up * strength;
    } else {
        // METTRE ici le code pour lorsque le bouton est relaché
    }
}
  
}


    public Sprite[] sprites;
    public float strength = 5f;
    public float gravity = -9.81f;
    public float tilt = 5f;

    private SpriteRenderer spriteRenderer;
    private Vector3 direction;
    private int spriteIndex;

    private void Awake()
    {
        spriteRenderer = GetComponent<SpriteRenderer>();
    }

    private void Start()
    {
        InvokeRepeating(nameof(AnimateSprite), 0.15f, 0.15f);

        oscReceiver.Bind("/BUTTON", TraiterOscBUTTON); //important
    }

    private void OnEnable()
    {
        Vector3 position = transform.position;
        position.y = 0f;
        transform.position = position;
        direction = Vector3.zero;
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space) || Input.GetMouseButtonDown(0)) {
            direction = Vector3.up * strength;
        }

        // Apply gravity and update the position
        direction.y += gravity * Time.deltaTime;
        transform.position += direction * Time.deltaTime;

        // Tilt the bird based on the direction
        Vector3 rotation = transform.eulerAngles;
        rotation.z = direction.y * tilt;
        transform.eulerAngles = rotation;
    }

    private void AnimateSprite()
    {
        spriteIndex++;

        if (spriteIndex >= sprites.Length) {
            spriteIndex = 0;
        }

        if (spriteIndex < sprites.Length && spriteIndex >= 0) {
            spriteRenderer.sprite = sprites[spriteIndex];
        }
    }

    private void OnTriggerEnter2D(Collider2D other)
    {
        if (other.gameObject.CompareTag("Obstacle")) {
            GameManager.Instance.GameOver();
        } else if (other.gameObject.CompareTag("Scoring")) {
            GameManager.Instance.IncreaseScore();
        }
    }

}
