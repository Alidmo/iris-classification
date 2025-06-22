# tests/test_model.py
import numpy as np
from src.model import train_model, predict
from src.data_loader import load_iris_data

def test_model_accuracy():
    df = load_iris_data()
    X = df.drop('target', axis=1)
    y = df['target']
    model = train_model(X, y, test_size=0.2, random_state=0)
    preds = predict(model, X)
    acc = np.mean(preds == y)
    # Should learn easily—training accuracy > 90%
    assert acc > 0.9
