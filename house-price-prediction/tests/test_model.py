# tests/test_model.py
import numpy as np
from model import train_model, predict
from data_loader import load_housing_data

def test_model_predict_shape():
    df = load_housing_data()
    X = df.drop('MedHouseVal', axis=1)
    y = df['MedHouseVal']
    model = train_model(X, y)
    preds = predict(model, X.iloc[:10])
    assert isinstance(preds, np.ndarray)
    assert preds.shape == (10,)
